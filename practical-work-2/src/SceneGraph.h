#pragma once

#include <vector>
#include <string>
#include "Appearance.h"
#include "Animation.h"
#include "Primitive.h"
#include "Transform.h"
#include "Point3D.h"
using namespace std;

struct Matrix {
	float matrix[16];
};

class Node {
private:
	bool parsed;
	string id;
	bool displaylist;
	unsigned int displayListID;
	Appearance* appearance;
	Animation* animation;
	vector<Node*> descendants;
	vector<string> descendantsIds;
	vector<Primitive*> primitives;
	Matrix transforms;
	Point3D* deltaAnimation;

public:
	Node(const string& id, const string& displaylist, Appearance* appearance,
			Animation* animation, const vector<string>& descendantsIds,
			const vector<Primitive*>& primitives, Matrix transforms);
	~Node();

	void addDescendant(Node* node);
	void draw(Appearance* parentAppearance);
	void generateGeometry(Appearance* parentAppearance);
	Appearance* getAppearance();
	Animation* getAnimation();
	string getID();
	const vector<Node*>& getDescendants();
	const vector<string>& getDescendantsIds();
	unsigned int getDisplayListID();
	const vector<Primitive*>& getPrimitives();
	Matrix getTransforms();
	bool getParsed();
	bool isDisplayList();
	void setAppearance(Appearance* appearance);
	void setAnimation(Animation* animation);
	void setDisplayListID(unsigned int id);
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
	void update();
	Node* getRoot();
	void setRoot(Node* node);
	string toString();
};
