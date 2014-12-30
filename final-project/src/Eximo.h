#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

enum Cell {
	EMPTY_CELL, WHITE_CELL, BLACK_CELL
};

enum Player {
	PLAYER_1, PLAYER_2
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
};
