#include "Cylinder.h"

#include "GL/glu.h"

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
}
