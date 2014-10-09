#include "Torus.h"

#include "GL/glut.h"

Torus::Torus(float inner, float outer, int slices, int loops) :
		Primitive(TORUS) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

Torus::~Torus() {
}

void Torus::draw() {
	glutSolidTorus(inner, outer, slices, loops);
}
