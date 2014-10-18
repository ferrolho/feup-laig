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

	return xyz;
}

float* Point3D::getXYZW() {
	xyzw[0] = x;
	xyzw[1] = y;
	xyzw[2] = z;
	xyzw[3] = 1;

	return xyzw;
}

string Point3D::toString() {
	stringstream ss;

	ss << x << " " << y << " " << z;

	return ss.str();
}
