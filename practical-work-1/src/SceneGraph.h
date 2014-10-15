#pragma once

#include <vector>
#include <string>
#include "Appearance.h"
#include "Primitive.h"
#include "Transform.h"
#include "PrimitiveType.h"
using namespace std;

struct Matrix {
	float matrix[16];
};

class Node {
private:
	string id;
	Appearance* appearance;
	vector<Node*> descendants;
	vector<string> descendantsIds;
	vector<Primitive*> primitives;
	Matrix transforms;

public:
	Node(const string& id, Appearance* appearance,
			const vector<string>& descendantsIds,
			const vector<Primitive*>& primitives, Matrix transforms);
	Node(const Node* node);

	void addDescendant(Node* node);
	void addPrimitive(Primitive* primitive);
	void draw(unsigned int level);
	string getID();
	const vector<Node*>& getDescendants();
	const vector<string>& getDescendantsIds();
	const vector<Primitive*>& getPrimitives();
	Matrix getTransforms();
	string toString(unsigned int level);
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
