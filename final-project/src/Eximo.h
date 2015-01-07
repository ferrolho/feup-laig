#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Connection.h"
#include "Scoreboard.h"
#include "EximoUtilities.h"
using namespace std;

class GhostCell: public CGFobject {
private:
	float size;
	CGFappearance* appearance;

public:
	GhostCell();
	~GhostCell();

	void draw();
	void draw(Point2D cell);
};

class EximoGame {
public:
	vector<vector<Cell> > board;
	pair<int, int> numPlayerPieces;
	Player currentPlayer;
	GameMode gameMode;

	EximoGame();
	EximoGame(const EximoGame* eximoGame);
};

class Eximo {
private:
	EximoGame* eximoGame;
	EximoGame* tempGame;
	vector<EximoGame*> history;

	SceneGraph* graph;
	Node* whiteChecker;
	Node* blackChecker;
	Node* whitePlayerDrawer;
	Node* blackPlayerDrawer;
	Scoreboard* scoreboard;

	LinearAnimation* moveCheckerAnim;
	Point2D movingCheckerDest;
	Player movingCheckerOwner;

	bool capturingChecker;
	LinearAnimation* captureCheckerAnim;
	Point2D captureCell;
	Player capturedCheckerOwner;

public:
	Point2D srcCell, destCell;

	bool reviewingGame;
	unsigned reviewStep;
	unsigned lastTime, reviewFrameTime, reviewFrameMaxTime;

	///////////

	Eximo(SceneGraph* graph, Scoreboard* scoreboard, const string& eximo);
	virtual ~Eximo();

	void update(unsigned long sysTime);
	void draw();

	void update(Message* message);
	void moveChecker(Point2D src, Point2D dest);
	void captureChecker();

	bool historyIsEmpty();
	void saveTempGameToHistory();
	void popHistory();

	EximoGame* getEximoGame();
	string getCurrentPlayer();

	EximoGame* getTempGame();
	void updateTempGame();

	void parsePrologString(const string& str);
	void parsePrologBoardString(const string& str);
	void parsePrologRemainingString(const string& str);

	void toggleCheckerNode(Node* newPiece,
			Appearance* whiteApp, Appearance* blackAp);

	string toString();
	string toPrologString();
};
