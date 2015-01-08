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
	friend class Eximo;

private:
	vector<vector<Cell> > board;
	pair<int, int> numPlayerPieces;
	Player currentPlayer;
	GameMode gameMode;

public:
	EximoGame();
	EximoGame(const EximoGame* eximoGame);
};

class Eximo {
	friend class GraphScene;

private:
	EximoGame* eximoGame;
	EximoGame* tempGame;
	vector<EximoGame*> history;

	float cellSize;
	float originX, originY;

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

	Point2D srcCell, destCell;

	bool reviewingGame;
	unsigned lastTime;
	unsigned reviewStep;
	unsigned reviewFrameTime, reviewFrameMaxTime;

public:
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

	void toggleCheckerNode(Node* whiteChecker, Node* blackChecker);

	string toString();
	string toPrologString();
};
