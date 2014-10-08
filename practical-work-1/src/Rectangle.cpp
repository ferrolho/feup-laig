#include "Rectangle.h"

#include "CGFobject.h"
#include "PrimitiveType.h"

Rectangle::Rectangle(Point3D p1, Point3D p2) :
		Primitive(RECTANGLE) {
	this->p1 = p1;
	this->p2 = p2;
}

Rectangle::~Rectangle() {
}

void Rectangle::draw() {
	glBegin(GL_QUADS);
	glVertex3d(p1.getX(), p1.getY(), 0);
	glVertex3d(p2.getX(), p1.getY(), 0);
	glVertex3d(p2.getX(), p2.getY(), 0);
	glVertex3d(p1.getX(), p2.getY(), 0);
	glEnd();
}
