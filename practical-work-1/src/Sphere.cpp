#include "Sphere.h"

#include "GL/glu.h"

Sphere::Sphere(float radius, int slices, int stacks) :
		Primitive(SPHERE) {
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
