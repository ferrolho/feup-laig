#include "Sphere.h"

Sphere::Sphere(float radius, int slices, int stacks) :
		Primitive(SPHERE) {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

Sphere::~Sphere() {
}
