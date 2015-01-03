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

Eximo::Eximo(Node* whiteChecker, Node* blackChecker, const string& eximo) {
	parsePrologString(eximo);
	this->whiteChecker = whiteChecker;
	this->blackChecker = blackChecker;
}

Eximo::~Eximo() {
}

void Eximo::update(Message* message) {
	if (message->isValid())
		parsePrologString(message->getContent());
}

float cellSize = 10.0 / 4.0;
float originX = -10 + cellSize / 2;
float originY = -10 + cellSize / 2;

void Eximo::draw() {
	for (unsigned i = 0; i < board.size(); i++) {
		for (unsigned j = 0; j < board[i].size(); j++) {
			glPushMatrix();

			glTranslatef(originX + j * cellSize, 0, originY + i * cellSize);

			switch (board[i][j]) {
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

string Eximo::getCurrentPlayer() {
	return playerToString(currentPlayer);
}

void Eximo::parsePrologString(const string& str) {
	parsePrologBoardString(str);
	parsePrologRemainingString(str);
}

void Eximo::parsePrologBoardString(const string& str) {
	// clear previous board
	board.clear();

	// get substring representing the current board
	string boardStr = getSubstringBetween(str, "[[[", "]]");

	// explode that string to a vector of strings
	vector<string> rawBoard = explodeString(boardStr, "[,]");

	vector<Cell> boardLine;
	int boardSize = sqrt(rawBoard.size());

	for (unsigned int i = 0; i < rawBoard.size(); i++) {
		boardLine.push_back(stringToCell(rawBoard[i]));

		if ((i + 1) % boardSize == 0) {
			board.push_back(boardLine);
			boardLine.clear();
		}
	}
}

void Eximo::parsePrologRemainingString(const string& str) {
	string piecesStr = getSubstringBetween(str, "]],[", "");

	// explode that string to a vector of strings
	vector<string> vec = explodeString(piecesStr, "[,]");

	numPlayerPieces.first = atoi(vec[0].c_str());
	numPlayerPieces.second = atoi(vec[1].c_str());

	currentPlayer = stringToPlayer(vec[2]);

	gameMode = stringToGameMode(vec[3]);
}

string Eximo::toString() {
	stringstream ss;

	ss << "---- Eximo.toString() ----------------------" << endl;

	ss << "Board:" << endl;
	for (unsigned i = 0; i < board.size(); i++) {
		for (unsigned j = 0; j < board[i].size(); j++) {
			if (j != 0)
				ss << " ";

			ss << board[i][j];
		}

		ss << endl;
	}

	ss << "Player pieces: " << numPlayerPieces.first << " - "
			<< numPlayerPieces.second << endl;

	ss << "Current player turn: " << playerToString(currentPlayer) << endl;

	ss << "Game mode: " << gameModeToString(gameMode) << endl;

	ss << "--------------------------------------------" << endl;

	return ss.str();
}

string Eximo::toPrologString() {
	stringstream ss;

	// board
	ss << "[[";
	for (unsigned i = 0; i < board.size(); i++) {
		if (i != 0)
			ss << ",";
		ss << "[";

		for (unsigned j = 0; j < board[i].size(); j++) {
			if (j != 0)
				ss << ",";

			ss << cellToString(board[i][j]);
		}

		ss << "]";
	}
	ss << "],";

	// number of pieces of each player
	ss << "[" << numPlayerPieces.first << "," << numPlayerPieces.second << "],";

	// current player turn
	ss << playerToString(currentPlayer) << ",";

	// game mode
	ss << gameModeToString(gameMode) << "]";

	return ss.str();
}
