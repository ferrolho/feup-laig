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
	bool hasBeenUsedByDisplayList;
	Appearance* appearance;
	Animation* animation;
	Point3D* deltaAnimation;
	vector<Node*>* descendants;
	vector<string>* descendantsIds;
	vector<Primitive*>* primitives;
	Matrix* transforms;

public:
	Node(const string& id, const string& displaylist, Appearance* appearance,
			Animation* animation, vector<string>* descendantsIds,
			vector<Primitive*>* primitives, Matrix* transforms);
	Node(Node& node);
	~Node();

	void addDescendant(Node* node);
	void draw(Appearance* parentAppearance);
	void generateGeometry(Appearance* parentAppearance);
	Animation* getAnimation();
	Appearance* getAppearance() const;
	string getID();
	vector<Node*>* getDescendants();
	vector<string>* getDescendantsIds();
	unsigned int getDisplayListID();
	bool getHasBeenUsedByDisplayList();
	vector<Primitive*>* getPrimitives();
	Matrix* getTransforms();
	bool getParsed() const;
	bool isDisplayList() const;
	void setAppearance(Appearance* appearance);
	void setAnimation(Animation* animation);
	void setDisplayListID(unsigned int id);
	void setHasBeenUsedByDisplayList(bool hasBeenUsedByDisplayList);
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
