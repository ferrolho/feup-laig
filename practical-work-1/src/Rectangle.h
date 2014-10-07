#pragma once

#include "Point3D.h"
#include "Primitive.h"

class Rectangle: public Primitive {
private:
	Point3D p1, p2;

public:
	Rectangle(Point3D p1, Point3D p2);
	virtual ~Rectangle();
};
