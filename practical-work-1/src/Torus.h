#pragma once

#include "Primitive.h"

class Torus: public Primitive {
private:
	float inner, outer;
	int slices, loops;

public:
	Torus(float inner, float outer, int slices, int loops);
	virtual ~Torus();

	void draw();
};
