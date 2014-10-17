#include "Scaling.h"

#include "CGFapplication.h"

Scaling::Scaling(Point3D factor) :
		Transform(SCALING) {
	this->factor = factor;
}

Scaling::~Scaling() {
}

void Scaling::apply() {
	glScalef(factor.getX(), factor.getY(), factor.getZ());
}
