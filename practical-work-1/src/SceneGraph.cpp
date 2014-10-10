#include "SceneGraph.h"

#include <sstream>
#include "GL/gl.h"
#include "Utilities.h"

Node::Node(string id, vector<string> descendantsIds,
		vector<Primitive*> primitives, Matrix transforms) {
	this->id = id;
	this->descendantsIds = descendantsIds;
	this->primitives = primitives;
	this->transforms = transforms;
}

void Node::addDescendant(Node* node) {
	descendants.push_back(node);
}

void Node::addPrimitive(Primitive* primitive) {
	primitives.push_back(primitive);
}

void Node::draw() {
	glPushMatrix();
	glMultMatrixf(transforms.matrix);

	foreach(primitives, primitive)
		(*primitive)->draw();

	foreach(descendants, descendant)
		(*descendant)->draw();

	glPopMatrix();
}

string Node::getID() {
	return id;
}

vector<Node*> Node::getDescendants() {
	return descendants;
}

vector<string> Node::getDescendantsIds() {
	return descendantsIds;
}

vector<Primitive*> Node::getPrimitives() {
	return primitives;
}

Matrix Node::getTransforms() {
	return transforms;
}

string Node::toString() {
	stringstream ss;

	ss << "id: " << id << endl;

	//for (int i = 0; i < getDescendants().size(); i++)
	//ss << getDescendants()[i]->toString() << endl;

	return ss.str();
}

SceneGraph::SceneGraph() {
	root = NULL;
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::draw() {
	root->draw();
}

Node* SceneGraph::getRoot() {
	return root;
}

void SceneGraph::setRoot(Node* node) {
	root = node;
}

string SceneGraph::toString() {
	stringstream ss;

	ss << root->toString() << endl;

	return ss.str();
}
