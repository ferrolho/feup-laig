#pragma once

#include <vector>
#include <string>
#include "Primitive.h"
using namespace std;

class Node {
private:
	string id;
	vector<Node*> descendants;
	vector<string> descendantsIds;
	vector<Primitive*> primitives;

public:
	Node(string id, vector<string> descendantsIds,
			vector<Primitive*> primitives);

	void addDescendant(Node* node);
	void addPrimitive(Primitive* primitive);
	void draw();
	string getID();
	vector<Node*> getDescendants();
	vector<string> getDescendantsIds();
	vector<Primitive*> getPrimitives();
};

class SceneGraph {
private:
	Node* root;

public:
	SceneGraph();
	virtual ~SceneGraph();

	void draw();
	Node* getRoot();
	void setRoot(Node* node);
};
