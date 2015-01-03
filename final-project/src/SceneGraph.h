#pragma once

#include <map>
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
	unsigned int currentAnimation;
	vector<Animation*>* animations;
	vector<Node*>* descendants;
	vector<string>* descendantsIds;
	vector<Primitive*>* primitives;
	Matrix* transforms;

public:
	Node(const string& id, const string& displaylist, Appearance* appearance,
			vector<Animation*>* animations, vector<string>* descendantsIds,
			vector<Primitive*>* primitives, Matrix* transforms);
	Node(Node& node);
	~Node();

	void update(unsigned long t);
	void draw(Appearance* parentAppearance);
	void applyAnimationToDescendants();
	void generateGeometry(Appearance* parentAppearance);

	void addDescendant(Node* node);
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
	void restartAnimation();
	void setAppearance(Appearance* appearance);
	void setDisplayListID(unsigned int id);
	void setHasBeenUsedByDisplayList(bool hasBeenUsedByDisplayList);
	void setParsed(bool parsed);
	string toString(unsigned int level);
};

class SceneGraph {
private:
	Node* root;
	map<string, Node*>* nodes;
	map<string, Texture*>* textures;
	int player1Ind, player2Ind;

public:
	SceneGraph();
	virtual ~SceneGraph();

	void update(unsigned long t);
	void draw();

	Node* getRoot();
	void setRoot(Node* node);

	map<string, Node*>* getNodes();
	void setNodes(map<string, Node*>* nodes);

	map<string, Texture*>* getTextures();
	void setTextures(map<string, Texture*>* textures);

	void initScoreboard();
	void setScoreboard(string player, string mode);
	void setPlayerScore(int playerNum);
	void setScoreboardLeaf(Node* node, int index);
	Node* findNodeByID(Node* node, string id);
	string processStringByNum(string prefixous, int index);

	string toString();
};
