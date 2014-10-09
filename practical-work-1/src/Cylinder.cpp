#include "Cylinder.h"

Cylinder::Cylinder(float base, float top, float height, int slices, int stacks) :
		Primitive(CYLINDER) {
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
}

Cylinder::~Cylinder() {
}

void Cylinder::draw() {
	gluCylinder(gluNewQuadric(), base, top, height, slices, stacks);

	// top face
	glPushMatrix();
	glTranslatef(0, 0, height);
	gluDisk(gluNewQuadric(), 0, top, slices, stacks);
	glPopMatrix();

	// base face
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	gluDisk(gluNewQuadric(), 0, base, slices, stacks);
	glPopMatrix();
}
