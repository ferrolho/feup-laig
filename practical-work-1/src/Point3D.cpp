#include "Point3D.h"

#include <sstream>

Point3D::Point3D() {
	x = y = z = 0;
}

Point3D::Point3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3D::~Point3D() {

}

float Point3D::getX() {
	return x;
}

float Point3D::getY() {
	return y;
}

float Point3D::getZ() {
	return z;
}

float* Point3D::getXYZ() {
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
	xyz[3] = 1;

	return xyz;
}

string Point3D::toString() {
	stringstream ss;

	ss << x << " " << y << " " << z;

	return ss.str();
}
