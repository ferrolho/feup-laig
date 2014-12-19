#pragma once

#include "AxisID.h"
#include "Transform.h"

#include <string>
using namespace std;

class Rotation: public Transform {
private:
	AxisID axis;
	float angle;

public:
	Rotation(const string& axis, float angle);
	Rotation(AxisID axis, float angle);
	virtual ~Rotation();

	void apply();
};
