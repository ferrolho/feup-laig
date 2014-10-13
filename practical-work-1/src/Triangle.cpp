#include "Triangle.h"

#include <vector>
#include "CGFobject.h"
#include "Utilities.h"

Triangle::Triangle(Point3D p1, Point3D p2, Point3D p3) :
		Primitive(TRIANGLE) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	vector<Point3D> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);

	normal = calculateSurfaceNormal(points);
}

Triangle::~Triangle() {
}

void Triangle::draw() {
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());

	glBegin(GL_TRIANGLES);
	glVertex3d(p1.getX(), p1.getY(), p1.getZ());
	glVertex3d(p2.getX(), p2.getY(), p2.getZ());
	glVertex3d(p3.getX(), p3.getY(), p3.getZ());
	glEnd();
}
