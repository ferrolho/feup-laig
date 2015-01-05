#pragma once

#include "SceneGraph.h"
#include "Clock.h"
#include "Animation.h"

using namespace std;

class ClockGame {
private:
	Node* box;
	Clock* clock;
	bool restart, pressed;

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
