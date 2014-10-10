#include "Rotation.h"

#include "GL/glu.h"

Rotation::Rotation(string axis, float angle) :
		Transform(ROTATION) {
	if (axis.compare("x") == 0 || axis.compare("X") == 0)
		this->axis = X;
	else if (axis.compare("y") == 0 || axis.compare("Y") == 0)
		this->axis = Y;
	else if (axis.compare("z") == 0 || axis.compare("Z") == 0)
		this->axis = Z;

	this->angle = angle;
}

Rotation::Rotation(AxisID axis, float angle) :
		Transform(ROTATION) {
	this->axis = axis;
	this->angle = angle;
}

Rotation::~Rotation() {
}

void Rotation::apply() {
	switch (axis) {
	case X:
		glRotatef(angle, 1, 0, 0);
		break;
	case Y:
		glRotatef(angle, 0, 1, 0);
		break;
	case Z:
		glRotatef(angle, 0, 0, 1);
		break;
	default:
		break;
	}
}
