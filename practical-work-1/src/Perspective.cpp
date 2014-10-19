#include "Perspective.h"

Perspective::Perspective(string id, float near, float far, float angle,
		Point3D* pos, Point3D* target) :
		Camera(id, near, far) {
	this->angle = angle;
	this->pos = pos;
	this->target = target;
}

Perspective::~Perspective() {

}

void Perspective::applyView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (pos->getX() - target->getX() == 0 && pos->getZ() - target->getZ() == 0)
		gluLookAt(pos->getX(), pos->getY(), pos->getZ(), target->getX(),
				target->getY(), target->getZ(), 0, 0, -1);
	else
		gluLookAt(pos->getX(), pos->getY(), pos->getZ(), target->getX(),
				target->getY(), target->getZ(), 0, 1, 0);
}

void Perspective::updateProjectionMatrix(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, (double) (width / height), near, far);
}

/*
 float Perspective::getAngle() {
 return angle;
 }

 Point3D* Perspective::getPos() {
 return pos;
 }

 Point3D* Perspective::getTarget() {
 return target;
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
 */
