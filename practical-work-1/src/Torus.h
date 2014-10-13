#pragma once

#include "Primitive.h"
#include "Point2D.h"
#include "Point3D.h"
#include <vector>

class Torus: public Primitive {
private:
	float inner, outer;
	unsigned int slices, loops;
	vector<Point2D*> texturePoints;
	vector<Point3D*> torusPoints, normalPoints;

public:
	Torus(float inner, float outer, unsigned int slices, unsigned int loops);
	virtual ~Torus();

	void draw();
};
