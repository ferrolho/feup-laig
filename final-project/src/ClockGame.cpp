#include "ClockGame.h"

ClockGame::ClockGame(Node* box, Clock* clock) {
	this->box = box;
	this->clock = clock;
	this->restart = false;
	this->pressed = false;
}

ClockGame::~ClockGame() {

}

Node* ClockGame::getBox() {
	return box;
}

Clock* ClockGame::getClock() {
	return clock;
}

void ClockGame::draw() {
	glPushMatrix();
	box->draw(NULL);
	glPopMatrix();

	clock->draw();
}

void ClockGame::update(unsigned long sysTime) {
	if (restart || pressed)
		if (!box->hasAllAnimationsDone())
			box->update(sysTime);
		else if (restart) {
			restart = false;
			clock->setPtrs();
			clock->clockIsOn = 1;
		} else
			pressed = false;
	else
		clock->update(sysTime);
}

void ClockGame::setClockGame() {
	restart = true;
	box->restartAnimation();
}

void ClockGame::pauseClock() {
	pressed = true;
	box->restartAnimation();
	clock->clockIsOn ? clock->clockIsOn = 0 : clock->clockIsOn = 1;
}
