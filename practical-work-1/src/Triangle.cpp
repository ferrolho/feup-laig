#include "Triangle.h"

#include "CGFobject.h"

Triangle::Triangle(Point3D p1, Point3D p2, Point3D p3) :
		Primitive(TRIANGLE) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	// start calculating texture points
	// sides length of triangle
	float a, b, c;

	a = sqrt(
			pow(p1.getX() - p3.getX(), 2) + pow(p1.getY() - p3.getY(), 2)
					+ pow(p1.getZ() - p3.getZ(), 2));

	b = sqrt(
				pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2)
						+ pow(p2.getZ() - p1.getZ(), 2));

	c = sqrt(
				pow(p3.getX() - p2.getX(), 2) + pow(p3.getY() - p2.getY(), 2)
						+ pow(p3.getZ() - p2.getZ(), 2));

	// cosine internal angles of triangle
	float beta, a_SinBeta, c_aCosBeta;

	beta = (pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c);

	c_aCosBeta = c - a*beta;
	a_SinBeta = sqrt(pow(b, 2) - pow(c_aCosBeta, 2));

	P0 = Point2D(c_aCosBeta, a_SinBeta);
	P1 = Point2D(0, 0);
	P2 = Point2D(c, 0);
}

Triangle::~Triangle() {
}

void Triangle::draw() {
	glBegin(GL_TRIANGLES);
	glVertex3d(p1.getX(), p1.getY(), p1.getZ());
	glVertex3d(p2.getX(), p2.getY(), p2.getZ());
	glVertex3d(p3.getX(), p3.getY(), p3.getZ());
	glEnd();
}
