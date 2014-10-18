#include "Sphere.h"

#include "CGFapplication.h"

Sphere::Sphere(float radius, int slices, int stacks) :
		Primitive() {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

Sphere::~Sphere() {
}

void Sphere::draw() {
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, radius, slices, stacks);
}
