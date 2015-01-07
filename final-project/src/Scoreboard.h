#pragma once

#include "SceneGraph.h"

using namespace std;

class Scoreboard {
private:
	Node* scoreboard;
	map<string, Texture*> textures;
	int player1, player2, activePlayer;
	bool change;
	Operation currentOperation;

public:
	Scoreboard();
	virtual ~Scoreboard();

	void init();
	void draw();
	void update(unsigned long sysTime);

	void setNode(Node* node);
	void setTextures(map<string, Texture*>& textures);

	void setScoreboard(Player player, Operation operation);
	void setPlayerScore(int playerNum, int pontuation, Operation op);
	void setScoreboardLeaf(Node* node, int index);

	void restartScoreboard();

	Node* findNodeByID(Node* node, string id);
};
