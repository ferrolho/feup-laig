#include "Eximo.h"

#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include "Utilities.h"

Cell stringToCell(const string& str) {
	if (str.compare("whiteCell") == 0)
		return WHITE_CELL;
	else if (str.compare("blackCell") == 0)
		return BLACK_CELL;
	else
		return EMPTY_CELL;
}

const string cellToString(Cell cell) {
	switch (cell) {
	case EMPTY_CELL:
		return "emptyCell";
	case WHITE_CELL:
		return "whiteCell";
	case BLACK_CELL:
		return "blackCell";
	default:
		return "???";
	}
}

Player stringToPlayer(const string& str) {
	if (str.compare("whitePlayer") == 0)
		return WHITE_PLAYER;
	else
		return BLACK_PLAYER;
}

const string playerToString(Player player) {
	switch (player) {
	case WHITE_PLAYER:
		return "whitePlayer";
	case BLACK_PLAYER:
		return "blackPlayer";
	default:
		return "???";
	}
}

GameMode stringToGameMode(const string& str) {
	if (str.compare("pvp") == 0)
		return PVP;
	else if (str.compare("pvb") == 0)
		return PVB;
	else
		return BVB;
}

const string gameModeToString(GameMode gameMode) {
	switch (gameMode) {
	case PVP:
		return "pvp";
	case PVB:
		return "pvb";
	case BVB:
		return "bvb";
	default:
		return "???";
	}
}

Eximo::Eximo(Node* whiteChecker, Node* blackChecker, const string& eximo,
		SceneGraph* graph, Scoreboard* scoreboard) {
	eximoGame = new EximoGame();
	tempGame = NULL;

	this->whiteChecker = whiteChecker;
	this->blackChecker = blackChecker;

	parsePrologString(eximo);

	this->graph = graph;

	this->scoreboard = scoreboard;

	moveCheckerAnim = NULL;

	capturingChecker = false;
	captureCheckerAnim = NULL;

	reviewingGame = false;
	reviewFrameMaxTime = 1000;
}

Eximo::~Eximo() {
}

void Eximo::update(unsigned long sysTime) {
	if (moveCheckerAnim) {
		moveCheckerAnim->update(sysTime);

		if (moveCheckerAnim->isDone()) {
			delete (moveCheckerAnim);
			moveCheckerAnim = NULL;

			if (capturingChecker) {
				movingCheckerOwner == WHITE_PLAYER ?
						(*graph->getNodes())["board-drawer-1"]->restartAnimation() :
						(*graph->getNodes())["board-drawer-2"]->restartAnimation();

				captureChecker(captureCell);
			}
		}
	}

	if (captureCheckerAnim) {
		captureCheckerAnim->update(sysTime);

		if (captureCheckerAnim->isDone()) {
			delete (captureCheckerAnim);
			captureCheckerAnim = NULL;

			capturingChecker = false;
		}
	}

	if (reviewingGame) {
		if (!lastTime)
			lastTime = sysTime;

		unsigned deltaTime = sysTime - lastTime;
		lastTime = sysTime;

		reviewFrameTime += deltaTime;

		if (reviewFrameTime > reviewFrameMaxTime) {
			reviewFrameTime = reviewFrameTime - reviewFrameMaxTime;

			reviewStep++;

			if (reviewStep >= history.size())
				reviewingGame = false;
		}
	}
}

float cellSize = 10.0 / 4.0;
float originX = -10 + cellSize / 2;
float originY = -10 + cellSize / 2;

void Eximo::draw() {
	if (!reviewingGame) {
		for (unsigned i = 0; i < eximoGame->board.size(); i++) {
			for (unsigned j = 0; j < eximoGame->board[i].size(); j++) {
				if (moveCheckerAnim)
					if (movingCheckerDest.getX() == i
							&& movingCheckerDest.getY() == j)
						continue;

				glPushMatrix();

				glTranslatef(originX + j * cellSize, 0, originY + i * cellSize);

				switch (eximoGame->board[i][j]) {
				case WHITE_CELL:
					whiteChecker->draw(NULL);
					break;
				case BLACK_CELL:
					blackChecker->draw(NULL);
					break;
				case EMPTY_CELL:
					break;
				default:
					break;
				}

				glPopMatrix();
			}
		}

		// drawing moving checker
		if (moveCheckerAnim) {
			glPushMatrix();

			moveCheckerAnim->apply();

			movingCheckerOwner == WHITE_PLAYER ?
					whiteChecker->draw(NULL) : blackChecker->draw(NULL);

			glPopMatrix();
		}

		if (capturingChecker) {
			glPushMatrix();

			if (captureCheckerAnim)
				captureCheckerAnim->apply();
			else
				glTranslated(originY + captureCell.getY() * cellSize, 0,
						originX + captureCell.getX() * cellSize);

			capturedCheckerOwner == WHITE_PLAYER ?
					whiteChecker->draw(NULL) : blackChecker->draw(NULL);

			glPopMatrix();
		}
	} else {
		for (unsigned i = 0; i < history[reviewStep]->board.size(); i++) {
			for (unsigned j = 0; j < history[reviewStep]->board[i].size();
					j++) {
				glPushMatrix();

				glTranslatef(originX + j * cellSize, 0, originY + i * cellSize);

				switch (history[reviewStep]->board[i][j]) {
				case WHITE_CELL:
					whiteChecker->draw(NULL);
					break;
				case BLACK_CELL:
					blackChecker->draw(NULL);
					break;
				case EMPTY_CELL:
					break;
				default:
					break;
				}

				glPopMatrix();
			}
		}
	}
}

void Eximo::update(Message* message) {
	if (message->isValid())
		parsePrologString(message->getContent());
}

void Eximo::moveChecker(Point2D src, Point2D dest) {
	// TODO work here
	vector<Point3D*> vec;

	Point3D* realSrc = new Point3D(originY + src.getY() * cellSize, 0,
			originX + src.getX() * cellSize);

	Point3D* realDest = new Point3D(originY + dest.getY() * cellSize, 0,
			originX + dest.getX() * cellSize);

	Point3D* realMiddle = new Point3D(
			realSrc->getX() + (realDest->getX() - realSrc->getX()) / 2.0, 1,
			realSrc->getZ() + (realDest->getZ() - realSrc->getZ()) / 2.0);

	vec.push_back(realSrc);
	vec.push_back(realMiddle);
	vec.push_back(realDest);

	moveCheckerAnim = new LinearAnimation("moveCheckerAnim", 1, vec);
	movingCheckerDest = dest;
	movingCheckerOwner = eximoGame->currentPlayer;

	moveCheckerAnim->restart();
}

void Eximo::captureChecker(Point2D cell) {
	// TODO work here
	vector<Point3D*> vec;

	Point3D* realSrc = new Point3D(originY + cell.getY() * cellSize, 0,
			originX + cell.getX() * cellSize);

	int destZ = 14;
	if (movingCheckerOwner != WHITE_PLAYER)
		destZ *= -1;

	Point3D* realMiddle = new Point3D(0, 3, destZ);

	Point3D* realDest = new Point3D(0, -2, destZ);

	vec.push_back(realSrc);
	vec.push_back(realMiddle);
	vec.push_back(realDest);

	captureCheckerAnim = new LinearAnimation("captureCheckerAnim", 3, vec);

	captureCheckerAnim->restart();
}

bool Eximo::historyIsEmpty() {
	return history.empty();
}

void Eximo::saveToHistory(EximoGame* eximoGame) {
	history.push_back(eximoGame);

	printf("history updated. current size: %lu\n", history.size());
}

void Eximo::popHistory() {
	if (history.empty()) {
		printf("can not undo move. no move has been made yet.\n");
	} else {
		eximoGame = history.back();
		tempGame = new EximoGame(getEximoGame());

		history.pop_back();

		printf("popped history. current size: %lu. current game updated\n",
				history.size());
	}
}

EximoGame* Eximo::getEximoGame() {
	return eximoGame;
}

string Eximo::getCurrentPlayer() {
	return playerToString(eximoGame->currentPlayer);
}

void Eximo::parsePrologString(const string& str) {
	parsePrologBoardString(str);
	parsePrologRemainingString(str);
}

void Eximo::parsePrologBoardString(const string& str) {
	// clear previous board
	eximoGame->board.clear();

	// get substring representing the current board
	string boardStr = getSubstringBetween(str, "[[[", "]]");

	// explode that string to a vector of strings
	vector<string> rawBoard = explodeString(boardStr, "[,]");

	vector<Cell> boardLine;
	int boardSize = sqrt(rawBoard.size());

	for (unsigned int i = 0; i < rawBoard.size(); i++) {
		boardLine.push_back(stringToCell(rawBoard[i]));

		if ((i + 1) % boardSize == 0) {
			eximoGame->board.push_back(boardLine);
			boardLine.clear();
		}
	}
}

void Eximo::parsePrologRemainingString(const string& str) {
	string piecesStr = getSubstringBetween(str, "]],[", "");

	// explode that string to a vector of strings
	vector<string> vec = explodeString(piecesStr, "[,]");

	int numWhitePlayerPieces = atoi(vec[0].c_str());
	int numBlackPlayerPieces = atoi(vec[1].c_str());

	if (eximoGame->numPlayerPieces.first == -1)
		eximoGame->numPlayerPieces.first = numWhitePlayerPieces;
	else if (numWhitePlayerPieces != eximoGame->numPlayerPieces.first) {
		// if player no. pieces changed, update scoreboard
		if (eximoGame->numPlayerPieces.first - numWhitePlayerPieces > 0) {
			scoreboard->setScoreboard(WHITE_PLAYER, DEC);

			captureCell.setX(
					srcCell.getX() + (destCell.getX() - srcCell.getX()) / 2);
			captureCell.setY(
					srcCell.getY() + (destCell.getY() - srcCell.getY()) / 2);
			capturingChecker = true;
			capturedCheckerOwner = WHITE_PLAYER;
		} else
			scoreboard->setScoreboard(WHITE_PLAYER, INC);

		eximoGame->numPlayerPieces.first = numWhitePlayerPieces;
	}

	if (eximoGame->numPlayerPieces.second == -1)
		eximoGame->numPlayerPieces.second = numBlackPlayerPieces;
	else if (numBlackPlayerPieces != eximoGame->numPlayerPieces.second) {
		// if player no. pieces changed, update scoreboard
		if (eximoGame->numPlayerPieces.second - numBlackPlayerPieces > 0) {
			scoreboard->setScoreboard(BLACK_PLAYER, DEC);

			captureCell.setX(
					srcCell.getX() + (destCell.getX() - srcCell.getX()) / 2);
			captureCell.setY(
					srcCell.getY() + (destCell.getY() - srcCell.getY()) / 2);
			capturingChecker = true;
			capturedCheckerOwner = BLACK_PLAYER;
		} else
			scoreboard->setScoreboard(BLACK_PLAYER, INC);

		eximoGame->numPlayerPieces.second = numBlackPlayerPieces;
	}

	eximoGame->currentPlayer = stringToPlayer(vec[2]);

	eximoGame->gameMode = stringToGameMode(vec[3]);
}

string Eximo::toString() {
	stringstream ss;

	ss << "---- Eximo.toString() ----------------------" << endl;

	ss << "Board:" << endl;
	for (unsigned i = 0; i < eximoGame->board.size(); i++) {
		for (unsigned j = 0; j < eximoGame->board[i].size(); j++) {
			if (j != 0)
				ss << " ";

			ss << eximoGame->board[i][j];
		}

		ss << endl;
	}

	ss << "Player pieces: " << eximoGame->numPlayerPieces.first << " - "
			<< eximoGame->numPlayerPieces.second << endl;

	ss << "Current player turn: " << playerToString(eximoGame->currentPlayer)
			<< endl;

	ss << "Game mode: " << gameModeToString(eximoGame->gameMode) << endl;

	ss << "--------------------------------------------" << endl;

	return ss.str();
}

string Eximo::toPrologString() {
	stringstream ss;

	// board
	ss << "[[";
	for (unsigned i = 0; i < eximoGame->board.size(); i++) {
		if (i != 0)
			ss << ",";
		ss << "[";

		for (unsigned j = 0; j < eximoGame->board[i].size(); j++) {
			if (j != 0)
				ss << ",";

			ss << cellToString(eximoGame->board[i][j]);
		}

		ss << "]";
	}
	ss << "],";

	// number of pieces of each player
	ss << "[" << eximoGame->numPlayerPieces.first << ","
			<< eximoGame->numPlayerPieces.second << "],";

	// current player turn
	ss << playerToString(eximoGame->currentPlayer) << ",";

	// game mode
	ss << gameModeToString(eximoGame->gameMode) << "]";

	return ss.str();
}
