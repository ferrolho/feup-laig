#pragma once

#include "Primitive.h"
#include "Point3D.h"
#include <math.h>
#include "GL/glu.h"
#include "GL/glui.h"

#define PI 3.14159265

class Cylinder: public Primitive {
private:
	float base, top, height;
	int slices, stacks;
	vector<Point3D*> topAndBasePoints;

public:
	Cylinder(float base, float top, float height, int slices, int stacks);
	virtual ~Cylinder();

	void draw();
};
