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
	Node(const string& id, const vector<string>& descendantsIds,
			const vector<Primitive*>& primitives, Matrix transforms);
	Node(const Node* node);

	void addDescendant(Node* node);
	void addPrimitive(Primitive* primitive);
	void draw(int level);
	string getID();
	const vector<Node*>& getDescendants();
	const vector<string>& getDescendantsIds();
	const vector<Primitive*>& getPrimitives();
	Matrix getTransforms();
	string toString(int level);
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
