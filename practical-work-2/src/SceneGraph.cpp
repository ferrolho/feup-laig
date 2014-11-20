#include "SceneGraph.h"

#include <sstream>
#include "CGFapplication.h"
#include "Utilities.h"

#include <cstdio>

Node::Node(const string& id, const string& displaylist, Appearance* appearance,
		Animation* animation, vector<string>* descendantsIds,
		vector<Primitive*>* primitives, Matrix* transforms) {
	parsed = false;
	this->id = id;
	displaylist.compare("true") == 0 ?
			this->displaylist = true : this->displaylist = false;
	displayListID = 0;
	hasBeenUsedByDisplayList = false;
	this->appearance = appearance;
	this->animation = animation;
	this->descendantsIds = descendantsIds;
	this->descendants = new vector<Node*>;
	this->primitives = primitives;
	this->transforms = transforms;
}

Node::Node(Node& node) {
	parsed = node.getParsed();
	id = node.getID();
	displaylist = node.isDisplayList();
	displayListID = node.getDisplayListID();
	hasBeenUsedByDisplayList = node.getHasBeenUsedByDisplayList();
	appearance = node.getAppearance();
	animation = node.animation;
	descendantsIds = node.getDescendantsIds();
	descendants = node.getDescendants();
	primitives = node.getPrimitives();
	transforms = node.getTransforms();
}

Node::~Node() {
	if (displaylist)
		glDeleteLists(displayListID, 1);
}

void Node::update(unsigned long t) {
	for (vector<Primitive*>::const_iterator it = primitives->begin();
			it != primitives->end(); it++)
		(*it)->update(t);

	if (animation)
		animation->update(t);

	for (vector<Node*>::const_iterator it = descendants->begin();
			it != descendants->end(); it++)
		(*it)->update(t);
}

void Node::draw(Appearance* parentAppearance, Animation* parentAnimation) {
	glPushMatrix();
	glMultMatrixf(transforms->matrix);

	if (animation)
		animation->apply();
	else if (parentAnimation)
		parentAnimation->apply();

	displaylist ?
			glCallList(displayListID) :
			generateGeometry(parentAppearance, parentAnimation);

	glPopMatrix();
}

void Node::generateGeometry(Appearance* parentAppearance,
		Animation* parentAnimation) {
	appearance ? appearance->apply() : parentAppearance->apply();

	/*if (animation)
	 animation->apply();
	 else if (parentAnimation)
	 parentAnimation->apply();*/

	for (vector<Primitive*>::const_iterator it = primitives->begin();
			it != primitives->end(); it++)
		(*it)->draw();

	for (vector<Node*>::const_iterator it = descendants->begin();
			it != descendants->end(); it++) {
		Appearance* descAppearance = appearance ? appearance : parentAppearance;
		Animation* descAnimation = animation ? animation : parentAnimation;

		(*it)->draw(descAppearance, descAnimation);
	}
}

void Node::addDescendant(Node* node) {
	descendants->push_back(node);
}

Appearance* Node::getAppearance() const {
	return appearance;
}

Animation* Node::getAnimation() {
	return animation;
}

string Node::getID() {
	return id;
}

vector<Node*>* Node::getDescendants() {
	return descendants;
}

vector<string>* Node::getDescendantsIds() {
	return descendantsIds;
}

unsigned int Node::getDisplayListID() {
	return displayListID;
}

bool Node::getHasBeenUsedByDisplayList() {
	return hasBeenUsedByDisplayList;
}

vector<Primitive*>* Node::getPrimitives() {
	return primitives;
}

Matrix* Node::getTransforms() {
	return transforms;
}

bool Node::getParsed() const {
	return parsed;
}

bool Node::isDisplayList() const {
	return displaylist;
}

void Node::restartAnimation() {
	if (animation)
		animation->reset();

	for (vector<Node*>::const_iterator it = descendants->begin();
			it != descendants->end(); it++)
		(*it)->restartAnimation();
}

void Node::setAppearance(Appearance* appearance) {
	this->appearance = appearance;

	for (unsigned int i = 0; i < primitives->size(); i++)
		(*primitives)[i]->updateTexture(appearance->getTexture());
}

void Node::setAnimation(Animation* animation) {
	this->animation = animation;
}

void Node::setDisplayListID(unsigned int id) {
	displayListID = id;
}

void Node::setHasBeenUsedByDisplayList(bool hasBeenUsedByDisplayList) {
	this->hasBeenUsedByDisplayList = hasBeenUsedByDisplayList;
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
		for (unsigned int i = 0; i < getDescendants()->size(); i++)
			ss << (*getDescendants())[i]->toString(level + 1);

	return ss.str();
}

SceneGraph::SceneGraph() {
	root = NULL;
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::update(unsigned long t) {
	root->update(t);
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
