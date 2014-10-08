#pragma once

#include <vector>
#include <string>
#include "Primitive.h"
using namespace std;

class Node {
private:
	string id;
	vector<Primitive*> primitives;
	vector<Node*> descendants;

public:
	Node(string id);

	string getID();
	void addPrimitive(Primitive* primitive);
	vector<Primitive*> getPrimitives();
};

class SceneGraph {
// TODO change to private
public:
	Node* root;

public:
	SceneGraph();
	virtual ~SceneGraph();
};
