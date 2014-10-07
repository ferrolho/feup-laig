#include "Triangle.h"

#include "PrimitiveType.h"

Triangle::Triangle(Point3D p1, Point3D p2, Point3D p3) :
		Primitive(TRIANGLE) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

Triangle::~Triangle() {
}
