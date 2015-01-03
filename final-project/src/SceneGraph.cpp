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
	nodes = NULL;
	player1Ind = 0;
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
	return nodes;
}

void SceneGraph::setNodes(map<string, Node*>* nodes) {
	this->nodes = nodes;
}

void SceneGraph::initScoreboard() {
	string p1 = "player-1", p2 = "player-2";
	if (player1Ind >= 0) {
		string teste = "leaf-2";
		if((*nodes)[teste]->getAppearance())
			cout << "TEM\n";

		(*nodes)[teste]->getAppearance()->setTexture("res/nums/number-1.png");

		/*(if (findNodeByID(root, "leaf-2", false)->getAppearance())
			cout << "Tem Appearance!\n";
		findNodeByID(root, "leaf-2")->getAppearance()->setTexture("res/nums/number-1.png");*/
	}
}

Node* SceneGraph::findNodeByID(Node* node, string id, bool found) {
	if (!found) {
		cout << "Nome do no: " << node->getID() << endl;

		if (node->getID().compare(id) == 0) {
			cout << "Nome do no ENCONTRADO: " << node->getID() << endl;
			found = true;
			return node;
		} else
			for (unsigned int i = 0; i < node->getDescendants()->size(); i++) {
				if (found)
					break;

				findNodeByID((*node->getDescendants())[i], id, found);
			}
	}

	return NULL;
}

string SceneGraph::toString() {
	stringstream ss;

	ss << root->toString(0);

	return ss.str();
}
