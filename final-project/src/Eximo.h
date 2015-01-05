#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Connection.h"
#include "SceneGraph.h"
#include "EximoUtilities.h"
using namespace std;

class EximoGame {
public:
	vector<vector<Cell> > board;
	pair<int, int> numPlayerPieces;
	Player currentPlayer;
	GameMode gameMode;

	EximoGame() {
		numPlayerPieces.first = -1;
		numPlayerPieces.second = -1;

		currentPlayer = WHITE_PLAYER;

		gameMode = PVP;
	}

	EximoGame(const EximoGame* eximoGame) {
		this->board = eximoGame->board;
		this->numPlayerPieces = eximoGame->numPlayerPieces;
		this->currentPlayer = eximoGame->currentPlayer;
		this->gameMode = eximoGame->gameMode;
	}
};

class Eximo {
private:
	EximoGame* eximoGame;
	vector<EximoGame*> history;

	LinearAnimation* moveCheckerAnim;
	Point2D movingCheckerDest;
	Player movingCheckerOwner;

	bool capturingChecker;
	LinearAnimation* captureCheckerAnim;
	Point2D captureCell;
	Player capturedCheckerOwner;

	SceneGraph* graph;
	Node* whiteChecker;
	Node* blackChecker;

public:
	EximoGame* tempGame;
	Point2D srcCell, destCell;

	bool reviewingGame;
	unsigned reviewStep;
	unsigned lastTime, reviewFrameTime, reviewFrameMaxTime;

	///////////

	Eximo(Node* whiteChecker, Node* blackChecker, const string& eximo,
			SceneGraph* graph);
	virtual ~Eximo();

	void update(unsigned long sysTime);
	void draw();

	void update(Message* message);
	void moveChecker(Point2D src, Point2D dest);
	void captureChecker(Point2D cell);

	bool historyIsEmpty();
	void saveToHistory(EximoGame* eximoGame);
	void popHistory();

	EximoGame* getEximoGame();
	string getCurrentPlayer();

	void parsePrologString(const string& str);
	void parsePrologBoardString(const string& str);
	void parsePrologRemainingString(const string& str);

	string toString();
	string toPrologString();
};
