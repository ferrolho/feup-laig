#include "SceneGraph.h"

#include <sstream>
#include "CGFapplication.h"
#include "Utilities.h"

#include <cstdio>

Node::Node(const string& id, Appearance* appearance,
		const vector<string>& descendantsIds,
		const vector<Primitive*>& primitives, Matrix transforms) {
	this->id = id;
	this->appearance = appearance;
	this->descendantsIds = descendantsIds;
	this->primitives = primitives;
	this->transforms = transforms;
}

Node::Node(const Node* node) {
	id = node->id;
	appearance = node->appearance;
	descendantsIds = node->descendantsIds;
	primitives = node->primitives;
	transforms = node->transforms;
}

void Node::addDescendant(Node* node, Appearance* parentAppearance) {
	descendants.push_back(node);

	if (!node->getAppearance() && parentAppearance)
		node->setAppearance(parentAppearance);
}

void Node::draw(unsigned int level) {
	glPushMatrix();
	glMultMatrixf(transforms.matrix);

	if (appearance)
		appearance->apply();

	for (vector<Primitive*>::const_iterator it = primitives.begin();
			it != primitives.end(); it++)
		(*it)->draw();

	if (level < maxLevels) {
		for (vector<Node*>::const_iterator it = descendants.begin();
				it != descendants.end(); it++) {
			// TODO if appearences bug, check if this makes any difference
			//if (appearance)
			//appearance->apply();

			(*it)->draw(level + 1);
		}
	}

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

void Node::setAppearance(Appearance* appearance) {
	this->appearance = appearance;

	for (unsigned int i = 0; i < primitives.size(); i++)
		primitives[i]->updateTexture(appearance->getTexture());
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
	root->draw(0);
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
