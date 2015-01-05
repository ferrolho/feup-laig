#include "Clock.h"

ClockHand::ClockHand(float size, Appearance* appearance) {
	this->appearance = appearance;

	pointer = new Cylinder(1.5, 1.5, 1.5, 12, 1);

	this->size = size;
	angle = 0;
}

void ClockHand::draw() {
	glPushMatrix();

	appearance->apply();

	glRotated(-angle, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	glScaled(0.02, 0.02, size);
	pointer->draw();

	glPopMatrix();
}

ClockHand::~ClockHand() {
	delete (pointer);
	delete (appearance);
}

float ClockHand::getAngle() {
	return angle;
}

void ClockHand::setAngle(float angle) {
	this->angle = angle;
}

void ClockHand::incAngle(float angle) {
	this->angle += angle;
	if (this->angle >= 360)
		this->angle -= 360;
}

Clock::Clock(Appearance* clockTex, Appearance* clockHandTex) {
	clockBody = new Cylinder(1.5, 1.5, 0.1, 60, 1);
	this->appearance = clockTex;

	minutesPtr = new ClockHand(0.6, clockHandTex);
	minutesPtr->setAngle(0);

	secondsPtr = new ClockHand(0.7, clockHandTex);
	secondsPtr->setAngle(0);

	savedTime = 0;
	clockIsOn = 1;
}

Clock::~Clock() {
	delete (appearance);
	delete (clockBody);
	delete (minutesPtr);
	delete (secondsPtr);
}
void Clock::update(unsigned long sysTime) {
	if (clockIsOn && sysTime != savedTime && savedTime != 0) {
		secondsPtr->incAngle((360.0 / 60) * (sysTime - savedTime) / 1000);
		minutesPtr->incAngle((360.0 / 60) * (sysTime - savedTime) / 1000 / 60);
	}

	savedTime = sysTime;
}

void Clock::draw() {
	glPushMatrix();

	glTranslated(16.55, -0.85, 0);
	glRotated(-90, 0, 1, 0);
	glRotated(-23, 1, 0, 0);
	appearance->apply();
	clockBody->draw();
	glTranslated(0, 0, 0.1);
	minutesPtr->draw();
	secondsPtr->draw();

	glPopMatrix();
}

void Clock::setTexture(string str) {
	appearance->setTexture(str);
}

void Clock::setPtrs() {
	minutesPtr->setAngle(0);
	secondsPtr->setAngle(0);
}

