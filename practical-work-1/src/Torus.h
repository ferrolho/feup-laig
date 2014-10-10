#pragma once

#include "Primitive.h"
#include "Point3D.h"
#include <vector>

class Torus: public Primitive {
private:
	float inner, outer;
	int slices, loops;
	vector<Point3D*> torusPoints;

public:
	Torus(float inner, float outer, int slices, int loops);
	virtual ~Torus();

	void draw();
};
