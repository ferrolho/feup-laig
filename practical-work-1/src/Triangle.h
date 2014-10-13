#pragma once

#include <math.h>

#include "Point2D.h"
#include "Point3D.h"
#include "Primitive.h"

class Triangle: public Primitive {
private:
	Point3D p1, p2, p3;
	Point2D P0, P1, P2;

public:
	Triangle(Point3D p1, Point3D p2, Point3D p3);
	virtual ~Triangle();

	void draw();
};
