#include "SceneGraph.h"

#include <cstdio>
#include "Utilities.h"

Node::Node(string id, vector<string> descendantsIds,
		vector<Primitive*> primitives) {
	this->id = id;
	this->descendantsIds = descendantsIds;
	this->primitives = primitives;
}

void Node::addDescendant(Node* node) {
	printf("adding descendant %s to %s\n", node->id.c_str(), id.c_str());
	descendants.push_back(node);
}

void Node::addPrimitive(Primitive* primitive) {
	primitives.push_back(primitive);
}

void Node::draw() {
	foreach(primitives, primitive)
		(*primitive)->draw();

	foreach(descendants, descendant)
		(*descendant)->draw();
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
