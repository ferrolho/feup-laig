#pragma once

#include <string>
#include "CGFapplication.h"
#include "Utilities.h"

using namespace std;

class Animation {
protected:
	string id;
	float span;
	bool done;
	unsigned long lastTime;

public:
	Animation(string id, float span);
	virtual ~Animation();

	virtual void restart();
	virtual void update(unsigned long sysTime) = 0;
	virtual void apply() = 0;

	string getId();
};

class CircularAnimation: public Animation {
private:
	Point3D* center;
	float radius, startAng, rotAng, endAng, ang, w;

public:
	CircularAnimation(string id, float span, Point3D* center, float radius,
			float startAngle, float rotAngle);
	virtual ~CircularAnimation();

	void restart();
	void update(unsigned long time);
	void apply();
};
