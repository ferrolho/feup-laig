#include "Rectangle.h"

#include "CGFobject.h"

Rectangle::Rectangle(Point3D p1, Point3D p2, Texture* texture) :
		Primitive() {
	this->p1 = p1;
	this->p2 = p2;
	this->s = 0;
	this->t = 0;
	this->texture = texture;

	if (texture) {
		s = getWidth() / this->texture->getTexLenght_s();
		t = getHeight() / this->texture->getTexLenght_t();
	}
}

Rectangle::~Rectangle() {
}

void Rectangle::draw() {
	glNormal3f(0, 0, 1);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3d(p1.getX(), p1.getY(), 0);

	glTexCoord2f(s, 0);
	glVertex3d(p2.getX(), p1.getY(), 0);

	glTexCoord2f(s, t);
	glVertex3d(p2.getX(), p2.getY(), 0);

	glTexCoord2f(0, t);
	glVertex3d(p1.getX(), p2.getY(), 0);

	glEnd();

	/*
	 // TODO try to add subdivisions to rectangles
	 glNormal3f(0, 0, 1);

	 int _numDivisions = getWidth() / 100;

	 for (int bx = 0; bx < _numDivisions; bx++) {
	 glBegin(GL_TRIANGLE_STRIP);

	 glTexCoord2d(1.0 * bx / _numDivisions, 0);
	 glVertex3f(bx, 0, 0);

	 for (int bz = 0; bz < _numDivisions; bz++) {
	 glTexCoord2f(1.0 * (bx + 1) / _numDivisions,
	 1.0 * bz / _numDivisions);
	 glVertex3f(bx + 1, 0, bz);

	 glTexCoord2f(1.0 * bx / _numDivisions,
	 1.0 * (bz + 1) / _numDivisions);
	 glVertex3f(bx, 0, bz + 1);
	 }

	 glTexCoord2d(1.0 * (bx + 1) / _numDivisions, 1);
	 glVertex3d(bx + 1, 0, _numDivisions);

	 glEnd();
	 }
	 */
}

float Rectangle::getHeight() {
	return abs(p2.getY() - p1.getY());
}

float Rectangle::getWidth() {
	return abs(p2.getX() - p1.getX());
}

void Rectangle::updateTexture(Texture* texture) {
	this->texture = texture;

	if (texture) {
		s = getWidth() / this->texture->getTexLenght_s();
		t = getHeight() / this->texture->getTexLenght_t();
	}
}
