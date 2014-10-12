#include "SceneGraph.h"

#include <sstream>
#include "GL/gl.h"
#include "Utilities.h"

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

void Node::addDescendant(Node* node) {
	descendants.push_back(new Node(node));
}

void Node::addPrimitive(Primitive* primitive) {
	primitives.push_back(primitive);
}

void Node::draw(unsigned int level) {
	glPushMatrix();
	glMultMatrixf(transforms.matrix);

	if (appearance)
		appearance->apply();

	foreach(primitives, primitive)
		(*primitive)->draw();

	if (level < maxLevels)
		foreach(descendants, descendant)
			(*descendant)->draw(level + 1);

	glPopMatrix();
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

string Node::toString(unsigned int level) {
	stringstream ss;

	FOR(i, 0, level)
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
}

string SceneGraph::toString() {
	stringstream ss;

	ss << root->toString(0);

	return ss.str();
}
