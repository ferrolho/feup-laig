#include "Scoreboard.h"

Scoreboard::Scoreboard() {
	this->scoreboard = NULL;
	this->player1 = 16;
	this->player2 = 16;
	this->activePlayer = 1;
	this->change = false;
	this->currentOperation = NONE;
}

Scoreboard::~Scoreboard() {

}

void Scoreboard::init() {
	vector<int> pontuations;
	pontuations.push_back(player1);
	pontuations.push_back(player2);

	for (unsigned z = 1; z <= 2; z++)
		for (unsigned i = 1; i <= 2; i++) {
			for (unsigned j = 1; j <= 4; j++) {
				stringstream ss;

				ss << "leaf-" << z << i << j;

				if (i == 1) {
					if (j == 4) {
						if (pontuations[z - 1] + 1 >= 0)
							setScoreboardLeaf(
									findNodeByID(scoreboard, ss.str()),
									(-1) / 10);
					} else
						setScoreboardLeaf(findNodeByID(scoreboard, ss.str()),
								(pontuations[z - 1] - j + 1) / 10);
				} else if (i == 2) {
					if (j == 4) {
						if (pontuations[z - 1] + 1 >= 0)
							setScoreboardLeaf(
									findNodeByID(scoreboard, ss.str()),
									(pontuations[z - 1] - 1) % 10);
					} else
						setScoreboardLeaf(findNodeByID(scoreboard, ss.str()),
								(pontuations[z - 1] - j + 1) % 10);
				}
			}
		}
}

void Scoreboard::draw() {
	scoreboard->draw(NULL);
}

void Scoreboard::update(unsigned long sysTime) {
	int pontuation;

	if (activePlayer == 1)
		pontuation = player1;
	else
		pontuation = player2;

	if (change) {
		if (!scoreboard->hasAllAnimationsDone()) {
			scoreboard->update(sysTime);

			if (scoreboard->hasAllAnimationsDone()) {
				for (unsigned i = 1; i <= 2; i++) {

					if (currentOperation == INC) {
						if (((pontuation - 1) / 10) == (pontuation / 10))
							i++;
					} else if (currentOperation == DEC)
						if (((pontuation + 1) / 10) == (pontuation / 10))
							i++;

					for (unsigned j = 1; j <= 4; j++) {
						stringstream ss;

						ss << "leaf-" << activePlayer << i << j;

						if (i == 1) {
							if (j == 4) {
								if (pontuation + 1 >= 0)
									setScoreboardLeaf(
											findNodeByID(scoreboard, ss.str()),
											(pontuation + 1) / 10);
							} else
								setScoreboardLeaf(
										findNodeByID(scoreboard, ss.str()),
										(pontuation - j + 1) / 10);
						} else if (i == 2) {
							if (j == 4) {
								if (pontuation + 1 >= 0)
									setScoreboardLeaf(
											findNodeByID(scoreboard, ss.str()),
											(pontuation + 1) % 10);
							} else
								setScoreboardLeaf(
										findNodeByID(scoreboard, ss.str()),
										(pontuation - j + 1) % 10);
						}

					}
				}
				change = false;
			}
		}
	}
}

void Scoreboard::setNode(Node* node) {
	scoreboard = node;
}

void Scoreboard::setTextures(map<string, Texture*>& textures) {
	this->textures = textures;
}

void Scoreboard::setScoreboard(Player player, Operation operation) {
	if (player == BLACK_PLAYER) {
		operation == INC ? ++player1 : --player1;
		if (player1 >= 0 && player1 <= 64) {
			activePlayer = 1, currentOperation = operation;
			setPlayerScore(activePlayer, player1, operation);
			change = true;
		}
	}

	else if (player == WHITE_PLAYER) {
		operation == INC ? ++player2 : --player2;
		if (player2 >= 0 && player2 <= 64) {
			activePlayer = 2, currentOperation = operation;
			setPlayerScore(activePlayer, player2, operation);
			change = true;
		}
	}
}

void Scoreboard::setPlayerScore(int playerNum, int pontuation, Operation op) {
	for (unsigned i = 1; i <= 2; i++) {

		if (op == INC) {
			if (((pontuation - 1) / 10) == (pontuation / 10))
				i++;
		} else if (op == DEC)
			if (((pontuation + 1) / 10) == (pontuation / 10))
				i++;

		for (unsigned j = 1; j <= 4; j++) {
			stringstream ss;

			ss << "leaf-" << playerNum << i << j;

			if (i == 1) {
				if (j == 4) {
					if (pontuation - 1 >= 0 && op == INC)
						findNodeByID(scoreboard, ss.str())->restartAnimation();
				} else if (op == DEC)
					findNodeByID(scoreboard, ss.str())->restartAnimation();
			} else if (i == 2) {
				if (j == 4) {
					if (pontuation - 1 >= 0 && op == INC)
						findNodeByID(scoreboard, ss.str())->restartAnimation();
				} else if (op == DEC)
					findNodeByID(scoreboard, ss.str())->restartAnimation();
			}
		}
	}
}

void Scoreboard::setScoreboardLeaf(Node* node, int index) {
	string format = "number-";

	cout << "Indice:" << index << endl;

// setting appearance changing the old for a new one
	node->setAppearance(new Appearance(node->getAppearance()));

// updating texture number
	node->getAppearance()->setTexture(
			textures[processStringByNum(format, index)]);
}

Node* Scoreboard::findNodeByID(Node* root, string id) {
	if (root) {
		if (root->getID().compare(id) == 0)
			return root;

		else {
			for (unsigned i = 0; i < root->getDescendants()->size(); i++) {
				Node* n = findNodeByID((*root->getDescendants())[i], id);

				if (n)
					return n;
			}
		}
	}

	return NULL;
}
