#pragma once

#include "Primitive.h"

class Cylinder: public Primitive {
private:
	float base, top, height;
	int slices, stacks;

public:
	Cylinder(float base, float top, float height, int slices, int stacks);
	virtual ~Cylinder();
};
