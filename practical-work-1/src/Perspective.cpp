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

void Perspective::applyView() {
	/*glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 gluLookAt(pos->getX(), pos->getY(), pos->getZ(), target->getX(),
	 target->getY(), target->getZ(), 0, 1, 0);*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 3.0, 7.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Perspective::updateProjectionMatrix(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, (double) width / (double) height, near, far);
}

bool Perspective::rotateTo(int axis, float angle, float increment) {
	increment = 0.5f;
	return false;
}

bool Perspective::rotate(int axis, float angle) {
	return false;
}

bool Perspective::setRotation(int axis, float angle) {
	return false;
}

bool Perspective::moveTo(int axis, float value, float increment) {
	increment = 0.5f;
	return false;
}

bool Perspective::translate(int axis, float value) {
	return false;
}
