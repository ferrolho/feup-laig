#pragma once

#include <string>

#include "Point3D.h"
#include "Utilities.h"

using namespace std;

class Animation {
private:
	string id;
	float span;

	Point3D* currentPosition;
	bool isFinished;

public:
	Animation(string id, float span);
	virtual ~Animation();

	virtual void init() = 0;
	virtual void apply() = 0;
	virtual void update() = 0;

	string getId();
	Point3D* getCurrentPosition();
};
