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

	Node* whiteChecker;
	Node* blackChecker;

public:
	Eximo(Node* whiteChecker, Node* blackChecker, const string& eximo);
	virtual ~Eximo();

	void update(Message* message);
	void draw();

	string getCurrentPlayer();

	void parsePrologString(const string& str);
	void parsePrologBoardString(const string& str);
	void parsePrologRemainingString(const string& str);

	string toString();
	string toPrologString();
};
