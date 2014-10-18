#include "Cylinder.h"

#include "CGFapplication.h"

Cylinder::Cylinder(float base, float top, float height, int slices, int stacks) :
		Primitive() {
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
}

Cylinder::~Cylinder() {
}

void Cylinder::draw() {
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	gluCylinder(quadric, base, top, height, slices, stacks);

	// top face
	glPushMatrix();
	glTranslatef(0, 0, height);
	gluDisk(quadric, 0, top, slices, stacks);
	glPopMatrix();

	// base face
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	gluDisk(quadric, 0, base, slices, stacks);
	glPopMatrix();
}
