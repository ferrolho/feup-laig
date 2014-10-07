#include "Rectangle.h"

#include "PrimitiveType.h"

Rectangle::Rectangle(Point3D p1, Point3D p2) :
		Primitive(RECTANGLE) {
	this->p1 = p1;
	this->p2 = p2;
}

Rectangle::~Rectangle() {
}
