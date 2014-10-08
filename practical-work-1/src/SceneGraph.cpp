#include "SceneGraph.h"

#include <iostream>

Node::Node(string id) {
	this->id = id;
}

string Node::getID() {
	return id;
}

void Node::addPrimitive(Primitive* primitive) {
	primitives.push_back(primitive);
}

vector<Primitive*> Node::getPrimitives() {
	return primitives;
}

SceneGraph::SceneGraph() {
	root = NULL;
}

SceneGraph::~SceneGraph() {

}
