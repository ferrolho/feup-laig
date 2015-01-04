#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Connection.h"
#include "SceneGraph.h"
#include "EximoUtilities.h"
using namespace std;

class Eximo {
private:
	vector<vector<Cell> > board;
	pair<int, int> numPlayerPieces;
	Player currentPlayer;
	GameMode gameMode;

	LinearAnimation* checkerAnim;
	Point2D movingCheckerDest;
	Player movingCheckerOwner;

	SceneGraph* graph;
	Node* whiteChecker;
	Node* blackChecker;

public:
	Eximo(Node* whiteChecker, Node* blackChecker, const string& eximo,
			SceneGraph* graph);
	virtual ~Eximo();

	void update(unsigned long sysTime);
	void draw();

	void update(Message* message);
	void moveChecker(Point2D src, Point2D dest);

	string getCurrentPlayer();

	void parsePrologString(const string& str);
	void parsePrologBoardString(const string& str);
	void parsePrologRemainingString(const string& str);

	string toString();
	string toPrologString();
};
