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
		s = getHeight() / this->texture->getTexLenght_s();
		t = getWidth() / this->texture->getTexLenght_t();
	}
}

Rectangle::~Rectangle() {
}

void Rectangle::draw() {
	glNormal3f(0, 0, 1);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3d(p1.getX(), p1.getY(), 0);

	glTexCoord2f(t, 0);
	glVertex3d(p2.getX(), p1.getY(), 0);

	glTexCoord2f(t, s);
	glVertex3d(p2.getX(), p2.getY(), 0);

	glTexCoord2f(0, s);
	glVertex3d(p1.getX(), p2.getY(), 0);

	glEnd();
}

float Rectangle::getHeight() {
	return abs(p2.getY() - p1.getY());
}

float Rectangle::getWidth() {
	return abs(p2.getX() - p1.getX());
}
