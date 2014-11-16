#include "SceneGraph.h"

#include <sstream>
#include "CGFapplication.h"
#include "Utilities.h"

#include <cstdio>

Node::Node(const string& id, const string& displaylist, Appearance* appearance,
		const vector<string>& descendantsIds,
		const vector<Primitive*>& primitives, Matrix transforms) {
	parsed = false;
	this->id = id;
	displaylist.compare("true") == 0 ?
			this->displaylist = true : this->displaylist = false;
	this->appearance = appearance;
	this->descendantsIds = descendantsIds;
	this->primitives = primitives;
	this->transforms = transforms;
}

void Node::addDescendant(Node* node) {
	descendants.push_back(node);
}

void Node::draw(Appearance* parentAppearance) {
	glPushMatrix();
	glMultMatrixf(transforms.matrix);

	(appearance) ? appearance->apply() : parentAppearance->apply();

	for (vector<Primitive*>::const_iterator it = primitives.begin();
			it != primitives.end(); it++)
		(*it)->draw();

	for (vector<Node*>::const_iterator it = descendants.begin();
			it != descendants.end(); it++)
		(appearance) ? (*it)->draw(appearance) : (*it)->draw(parentAppearance);

	glPopMatrix();
}

Appearance* Node::getAppearance() {
	return appearance;
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

const vector<Primitive*>& Node::getPrimitives() {
	return primitives;
}

Matrix Node::getTransforms() {
	return transforms;
}

bool Node::getParsed() {
	return parsed;
}

void Node::setAppearance(Appearance* appearance) {
	this->appearance = appearance;

	for (unsigned int i = 0; i < primitives.size(); i++)
		primitives[i]->updateTexture(appearance->getTexture());
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
	root->draw(root->getAppearance());
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
