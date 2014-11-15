#pragma once

#include <vector>
#include <string>
#include "Appearance.h"
#include "Primitive.h"
#include "Transform.h"
using namespace std;

struct Matrix {
	float matrix[16];
};

class Node {
private:
	bool parsed;
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

	void addDescendant(Node* node);
	void draw(Appearance* parentAppearance);
	Appearance* getAppearance();
	string getID();
	const vector<Node*>& getDescendants();
	const vector<string>& getDescendantsIds();
	const vector<Primitive*>& getPrimitives();
	Matrix getTransforms();
	bool getParsed();
	void setAppearance(Appearance* appearance);
	void setParsed(bool parsed);
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
