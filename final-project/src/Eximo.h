#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Connection.h"
using namespace std;

enum Cell {
	EMPTY_CELL, WHITE_CELL, BLACK_CELL
};

enum Player {
	WHITE_PLAYER, BLACK_PLAYER
};

enum GameMode {
	PVP, PVB, BVB
};

class Eximo {
private:
	vector<vector<Cell> > board;
	pair<int, int> numPlayerPieces;
	Player currentPlayer;
	GameMode gameMode;

public:
	Eximo(const string& eximo);
	virtual ~Eximo();

	void update(Message* message);

	void parsePrologString(const string& str);
	void parsePrologBoardString(const string& str);
	void parsePrologRemainingString(const string& str);

	string toString();
	string toPrologString();
};
