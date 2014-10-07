#include "Torus.h"

Torus::Torus(float inner, float outer, int slices, int loops) :
		Primitive(PrimitiveType::TORUS) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

Torus::~Torus() {

}
