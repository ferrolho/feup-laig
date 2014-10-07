#pragma once

#include "Primitive.h"

class Sphere: public Primitive {
private:
	float radius;
	int slices, stacks;

public:
	Sphere(float radius, int slices, int stacks);
	virtual ~Sphere();
};
