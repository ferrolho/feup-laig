#pragma once

#include "SceneGraph.h"
#include "Clock.h"

using namespace std;

class ClockGame {
private:
	Node* box;
	Clock* clock;
	bool restart;

public:
	ClockGame(Node* box, Clock* clock);
	virtual ~ClockGame();

	Node* getBox();
	Clock* getClock();
	void setClockGame();
	void pauseClock();

	void draw();
	void update(unsigned long sysTime);
};
