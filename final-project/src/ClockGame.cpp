#include "ClockGame.h"

ClockGame::ClockGame(Node* box, Clock* clock) {
	this->box = box;
	this->clock = clock;
	this->restart = false;

	cout << this->box->toString(0) << "AQUI\n" << endl;
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
	box->draw(NULL);
	clock->draw();
}

void ClockGame::update(unsigned long sysTime) {
	if (restart) {
		clock->setPtrs();
		restart = false;
	}

	clock->update(sysTime);
}

void ClockGame::setClockGame() {
	restart = true;
}

void ClockGame::pauseClock() {
	clock->clockIsOn ? clock->clockIsOn = 0 : clock->clockIsOn = 1;
}
