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

void Point3D::setPoint(Point3D p) {
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}

void Point3D::setPoint(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point3D::setX(float x) {
	this->x = x;
}

void Point3D::setY(float y) {
	this->y = y;
}

void Point3D::setZ(float z) {
	this->z = z;
}

string Point3D::toString() {
	stringstream ss;

	ss << x << ", " << y << ", " << z;

	return ss.str();
}
