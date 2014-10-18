#include "Triangle.h"

#include <vector>
#include "CGFobject.h"
#include "Utilities.h"

Triangle::Triangle(Point3D p1, Point3D p2, Point3D p3, Texture* texture) :
		Primitive() {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->s = 0;
	this->t = 0;
	this->texture = texture;

	vector<Point3D> points;
	points.push_back(this->p1);
	points.push_back(this->p2);
	points.push_back(this->p3);

	normal = calculateSurfaceNormal(points);

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

	c_aCosBeta = c - a * beta;
	a_SinBeta = sqrt(pow(b, 2) - pow(c_aCosBeta, 2));

	P0 = Point2D(c_aCosBeta, a_SinBeta);
	P1 = Point2D(0, 0);
	P2 = Point2D(c, 0);

	if (texture) {
		this->s = P2.getX() / texture->getTexLenght_s();
		this->t = P0.getY() / texture->getTexLenght_t();

		P2.setX(s);
		P0 = Point2D(s / 2, t);
	}
}

Triangle::~Triangle() {
}

void Triangle::draw() {
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());

	glBegin(GL_TRIANGLES);
	glTexCoord2f(P0.getX(), P0.getY());
	glVertex3d(p1.getX(), p1.getY(), p1.getZ());

	glTexCoord2f(P1.getX(), P1.getY());
	glVertex3d(p2.getX(), p2.getY(), p2.getZ());

	glTexCoord2f(P2.getX(), P2.getY());
	glVertex3d(p3.getX(), p3.getY(), p3.getZ());
	glEnd();
}

void Triangle::updateTexture(Texture* texture) {
	this->texture = texture;

	if (texture) {
		this->s = P2.getX() / texture->getTexLenght_s();
		this->t = P0.getY() / texture->getTexLenght_t();

		P2.setX(s);
		P0 = Point2D(s / 2, t);
	}
}
