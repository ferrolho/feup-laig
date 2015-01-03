#include "SceneGraph.h"

#include <sstream>
#include "CGFapplication.h"
#include "Utilities.h"

#include <cstdio>

Node::Node(const string& id, const string& displaylist, Appearance* appearance,
		vector<Animation*>* animations, vector<string>* descendantsIds,
		vector<Primitive*>* primitives, Matrix* transforms) {
	parsed = false;
	this->id = id;

	displaylist.compare("true") == 0 ?
			this->displaylist = true : this->displaylist = false;
	displayListID = 0;
	hasBeenUsedByDisplayList = false;

	this->appearance = appearance;

	currentAnimation = 0;
	this->animations = animations;

	this->descendantsIds = descendantsIds;
	this->descendants = new vector<Node*>;
	this->primitives = primitives;
	this->transforms = transforms;
}

Node::Node(Node& node) {
	parsed = node.getParsed();
	id = node.getID();
	displaylist = node.isDisplayList();
	displayListID = node.getDisplayListID();
	hasBeenUsedByDisplayList = node.getHasBeenUsedByDisplayList();
	appearance = node.getAppearance();
	currentAnimation = 0;
	animations = node.animations;
	descendantsIds = node.getDescendantsIds();
	descendants = node.getDescendants();
	primitives = node.getPrimitives();
	transforms = node.getTransforms();
}

Node::~Node() {
	if (displaylist)
		glDeleteLists(displayListID, 1);
}

void Node::update(unsigned long t) {
	for (vector<Primitive*>::const_iterator it = primitives->begin();
			it != primitives->end(); it++)
		(*it)->update(t);

	if (animations && (*animations)[currentAnimation]->isRunning()) {
		(*animations)[currentAnimation]->update(t);

		if ((*animations)[currentAnimation]->isDone())
			currentAnimation++;

		if (currentAnimation > animations->size() - 1) {
			for (unsigned int i = 0; i < animations->size(); i++)
				(*animations)[i]->resetValues();

			currentAnimation = 0;
		}
	}

	for (vector<Node*>::const_iterator it = descendants->begin();
			it != descendants->end(); it++)
		(*it)->update(t);
}

void Node::draw(Appearance* parentAppearance) {
	glPushMatrix();

	if (animations)
		for (unsigned int i = 0; i <= currentAnimation; i++)
			(*animations)[i]->apply();

	glMultMatrixf(transforms->matrix);

	if (displaylist)
		glCallList(displayListID);
	else
		generateGeometry(parentAppearance);

	glPopMatrix();
}

void Node::generateGeometry(Appearance* parentAppearance) {
	appearance ? appearance->apply() : parentAppearance->apply();

	for (vector<Primitive*>::const_iterator it = primitives->begin();
			it != primitives->end(); it++)
		(*it)->draw();

	for (vector<Node*>::const_iterator it = descendants->begin();
			it != descendants->end(); it++)
		(*it)->draw(appearance ? appearance : parentAppearance);
}

void Node::addDescendant(Node* node) {
	descendants->push_back(node);
}

Appearance* Node::getAppearance() const {
	return appearance;
}

string Node::getID() {
	return id;
}

vector<Node*>* Node::getDescendants() {
	return descendants;
}

vector<string>* Node::getDescendantsIds() {
	return descendantsIds;
}

unsigned int Node::getDisplayListID() {
	return displayListID;
}

bool Node::getHasBeenUsedByDisplayList() {
	return hasBeenUsedByDisplayList;
}

vector<Primitive*>* Node::getPrimitives() {
	return primitives;
}

Matrix* Node::getTransforms() {
	return transforms;
}

bool Node::getParsed() const {
	return parsed;
}

bool Node::isDisplayList() const {
	return displaylist;
}

void Node::restartAnimation() {
	currentAnimation = 0;

	if (animations)
		for (unsigned int i = 0; i < animations->size(); i++)
			if ((*animations)[i])
				(*animations)[i]->restart();

	for (vector<Node*>::const_iterator it = descendants->begin();
			it != descendants->end(); it++)
		(*it)->restartAnimation();
}

void Node::setAppearance(Appearance* appearance) {
	this->appearance = appearance;

	for (unsigned int i = 0; i < primitives->size(); i++)
		(*primitives)[i]->updateTexture(appearance->getTexture());
}

void Node::setDisplayListID(unsigned int id) {
	displayListID = id;
}

void Node::setHasBeenUsedByDisplayList(bool hasBeenUsedByDisplayList) {
	this->hasBeenUsedByDisplayList = hasBeenUsedByDisplayList;
}

void Node::setParsed(bool parsed) {
	this->parsed = parsed;
}

string Node::toString(unsigned int level) {
	stringstream ss;

	for (unsigned int i = 0; i < level; i++)
		ss << "  ";
	ss << "id: " << id << endl;

	if (level < maxLevels)
		for (unsigned int i = 0; i < getDescendants()->size(); i++)
			ss << (*getDescendants())[i]->toString(level + 1);

	return ss.str();
}

SceneGraph::SceneGraph() {
	root = NULL;
	//nodes = NULL;
	//textures = NULL;
	player1Ind = 10;
	player2Ind = 0;
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::update(unsigned long t) {
	root->update(t);
}

void SceneGraph::draw() {
	root->draw(root->getAppearance());
}

Node* SceneGraph::getRoot() {
	return root;
}

void SceneGraph::setRoot(Node* node) {
	root = node;

	if (!root->getAppearance())
		root->setAppearance(new Appearance());
}

map<string, Node*>* SceneGraph::getNodes() {
	return &nodes;
}

void SceneGraph::setNodes(map<string, Node*>& nodes) {
	this->nodes = nodes;
}

map<string, Texture*>* SceneGraph::getTextures() {
	return &textures;
}

void SceneGraph::setTextures(map<string, Texture*>& textures) {
	this->textures = textures;
}

void SceneGraph::initScoreboard() {
	string p1 = "player-score-1", p2 = "player-score-2";
	if (player1Ind >= 0) {
		setPlayerScore(1);
	}

	if (player2Ind >= 0) {
		setPlayerScore(2);
	}
}

void SceneGraph::setScoreboard(string player, string mode) {
	if (player1Ind >= 0 && player.compare("player1") == 0) {
		mode == "inc" ? ++player1Ind : --player1Ind;
		cout << "PLAYER1: " << player1Ind << endl;
		setPlayerScore(1);
	}

	if (player2Ind >= 0 && player.compare("player2") == 0) {
		mode == "inc" ? ++player2Ind : --player2Ind;
		cout << "PLAYER2: " << player2Ind << endl;
		setPlayerScore(2);
	}
}

void SceneGraph::setPlayerScore(int playerNum) {
	for (unsigned i = 1; i <= 2; i++)
		for (unsigned j = 1; j <= 4; j++) {
			stringstream ss;

			ss << "leaf-" << playerNum << i << j;
			cout << ss.str() << endl;
			cout << "Score: " << (player1Ind + j - 1) % 10 << endl;

			if (i == 1) {
				playerNum == 1 ?
						setScoreboardLeaf(nodes[ss.str()],
								(player1Ind + j - 1) / 10) :
						setScoreboardLeaf(nodes[ss.str()],
								(player2Ind + j - 1) / 10);
			} else if (i == 2) {
				cout << "ENTREI no 2\n" << endl;
				playerNum == 1 ?
						setScoreboardLeaf(nodes[ss.str()],
								(player1Ind + j - 1) % 10) :
						setScoreboardLeaf(nodes[ss.str()],
								(player2Ind + j - 1) % 10);
			}

			if (nodes[ss.str()])
				cout << nodes[ss.str()]->getID() << endl;
		}
}

void SceneGraph::setScoreboardLeaf(Node* node, int index) {
	string format = "number-";

	// setting appearance changing the old for a new one
	node->setAppearance(new Appearance(node->getAppearance()));

	// updating texture number
	node->getAppearance()->setTexture(
			textures[processStringByNum(format, index)]);
}

Node* SceneGraph::findNodeByID(Node* root, string id) {
	if (root) {
		if (root->getID().compare(id) == 0)
			return root;

		else {
			for (unsigned i = 0; i < root->getDescendants()->size(); i++) {
				Node* n = findNodeByID((*root->getDescendants())[i], id);

				if (n)
					return n;
			}
		}
	}

	return NULL;
}

string SceneGraph::processStringByNum(string prefixous, int index) {
	stringstream ss;

	ss << prefixous << index;

	return ss.str();
}

string SceneGraph::toString() {
	stringstream ss;

	ss << root->toString(0);

	return ss.str();
}
