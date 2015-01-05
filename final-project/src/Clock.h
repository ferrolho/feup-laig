#pragma once

#include "Cylinder.h"
#include "Appearance.h"
#include <iostream>

class ClockHand {
private:
	Appearance* appearance;
	Cylinder* pointer;
	float size, angle;

public:
	ClockHand(float size, Appearance* appearance);
	virtual ~ClockHand();

	void draw();

	float getAngle();
	void setAngle(float angle);
	void incAngle(float angle);
};

class Clock {
private:
	Appearance* appearance;
	Cylinder* clockBody;
	ClockHand* minutesPtr;
	ClockHand* secondsPtr;

	unsigned long savedTime;

public:
	Clock(Appearance* clockTex, Appearance* clockHandTex);
	virtual ~Clock();

	void update(unsigned long sysTime);
	void draw();

	void setTexture(string str);
	void setPtrs();

	int clockIsOn;
};
