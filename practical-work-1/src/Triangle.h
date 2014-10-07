#pragma once

#include "Point3D.h"
#include "Primitive.h"

class Triangle: public Primitive {
private:
	Point3D p1, p2, p3;

public:
	Triangle(Point3D p1, Point3D p2, Point3D p3);
	virtual ~Triangle();
};
