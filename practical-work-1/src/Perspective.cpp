#include "Perspective.h"

Perspective::Perspective() {
	this->angle = 0;
	this->pos = new Point3D();
	this->target = new Point3D(10, 10, 10);
}
Perspective::Perspective(Perspective* perspective) {
	this->angle = perspective->angle;
	this->pos = perspective->pos;
	this->target = perspective->target;
}

Perspective::Perspective(string id, float near, float far, float angle,
		Point3D* pos, Point3D* target) :
		Camera(id, near, far) {
	this->angle = angle;
	this->pos = pos;
	this->target = target;
}

Perspective::~Perspective() {

}

float Perspective::getAngle() {
	return angle;
}

Point3D* Perspective::getPos() {
	return pos;
}

Point3D* Perspective::getTarget() {
	return target;
}
