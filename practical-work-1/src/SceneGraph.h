#pragma once

#include <vector>
#include <string>
#include "Primitive.h"
#include "Transform.h"
using namespace std;

struct Matrix {
	float matrix[16];
};

class Node {
private:
	string id;
	vector<Node*> descendants;
	vector<string> descendantsIds;
	vector<Primitive*> primitives;
	Matrix transforms;

public:
	Node(string id, vector<string> descendantsIds,
			vector<Primitive*> primitives, Matrix transforms);

	void addDescendant(Node* node);
	void addPrimitive(Primitive* primitive);
	void draw();
	string getID();
	vector<Node*> getDescendants();
	vector<string> getDescendantsIds();
	vector<Primitive*> getPrimitives();
	Matrix getTransforms();
	string toString();
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
	string toString();
};
