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

#include <cstdio>

void Rotation::apply() {
	switch (axis) {
	case X:
		printf("rotating in x\n");
		glRotatef(angle, 1, 0, 0);
		break;
	case Y:
		printf("rotating in y\n");
		glRotatef(angle, 0, 1, 0);
		break;
	case Z:
		printf("rotating in z\n");
		glRotatef(angle, 0, 0, 1);
		break;
	default:
		break;
	}
}
