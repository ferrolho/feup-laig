#include "SceneGraph.h"

#include <sstream>
#include "CGFapplication.h"
#include "Utilities.h"

#include <cstdio>

Node::Node(const string& id, const string& displaylist, Appearance* appearance,
		Animation* animation, const vector<string>& descendantsIds,
		const vector<Primitive*>& primitives, Matrix transforms) {
	parsed = false;
	this->id = id;
	displaylist.compare("true") == 0 ?
			this->displaylist = true : this->displaylist = false;
	displayListID = 0;
	this->appearance = appearance;
	this->animation = animation;
	this->descendantsIds = descendantsIds;
	this->primitives = primitives;
	this->transforms = transforms;
}

Node::~Node() {
	if (displaylist)
		glDeleteLists(displayListID, 1);
}

void Node::addDescendant(Node* node) {
	descendants.push_back(node);
}

void Node::draw(Appearance* parentAppearance, Animation* parentAnimation) {
	glPushMatrix();
	glMultMatrixf(transforms.matrix);

	displaylist ?
			glCallList(displayListID) :
			generateGeometry(parentAppearance, parentAnimation);

	glPopMatrix();
}

void Node::generateGeometry(Appearance* parentAppearance,
		Animation* parentAnimation) {
	appearance ? appearance->apply() : parentAppearance->apply();

	animation ? animation->apply() : parentAnimation->apply();

	for (vector<Primitive*>::const_iterator it = primitives.begin();
			it != primitives.end(); it++)
		(*it)->draw();

	for (vector<Node*>::const_iterator it = descendants.begin();
			it != descendants.end(); it++)
		(appearance && animation) ?
				(*it)->draw(appearance, animation) :
				(*it)->draw(parentAppearance, parentAnimation);
}

Appearance* Node::getAppearance() {
	return appearance;
}

Animation* Node::getAnimation() {
	return animation;
}

string Node::getID() {
	return id;
}

const vector<Node*>& Node::getDescendants() {
	return descendants;
}

const vector<string>& Node::getDescendantsIds() {
	return descendantsIds;
}

unsigned int Node::getDisplayListID() {
	return displayListID;
}

const vector<Primitive*>& Node::getPrimitives() {
	return primitives;
}

Matrix Node::getTransforms() {
	return transforms;
}

bool Node::getParsed() {
	return parsed;
}

bool Node::isDisplayList() {
	return displaylist;
}

void Node::setAppearance(Appearance* appearance) {
	this->appearance = appearance;

	for (unsigned int i = 0; i < primitives.size(); i++)
		primitives[i]->updateTexture(appearance->getTexture());
}

void Node::setAnimation(Animation* animation) {
	this->animation = animation;
}

void Node::setDisplayListID(unsigned int id) {
	displayListID = id;
}

void Node::setParsed(bool parsed) {
	this->parsed = parsed;
}

string Node::toString(unsigned int level) {
	stringstream ss;

	for (unsigned int i = 0; i < level; i++)
		ss << "  ";
	ss << "id: " << id << endl;

	if (level < maxLevels)
		for (unsigned int i = 0; i < getDescendants().size(); i++)
			ss << getDescendants()[i]->toString(level + 1);

	return ss.str();
}

SceneGraph::SceneGraph() {
	root = NULL;
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::draw() {
	root->draw(root->getAppearance(), root->getAnimation());
}

Node* SceneGraph::getRoot() {
	return root;
}

void SceneGraph::setRoot(Node* node) {
	root = node;

	if (!root->getAppearance())
		root->setAppearance(new Appearance());
}

string SceneGraph::toString() {
	stringstream ss;

	ss << root->toString(0);

	return ss.str();
}
