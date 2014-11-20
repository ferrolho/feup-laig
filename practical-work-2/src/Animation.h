#pragma once

#include <string>

#include "CGFapplication.h"

#include "Point3D.h"
#include "Utilities.h"

using namespace std;

class Animation {
protected:
	string id;
	float span;

	Point3D* currentPosition;
	bool isFinished, start;
	float oldTime;

public:
	Animation(string id, float span);
	virtual ~Animation();

	virtual void init(unsigned long sysTime) = 0;
	virtual void apply() = 0;
	virtual void update(unsigned long sysTime) = 0;
	virtual void reset();

	string getId();
	Point3D* getCurrentPosition();
};
