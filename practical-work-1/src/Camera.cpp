#include "Camera.h"

Camera::Camera(string id, float near, float far, float angle, Point3D* pos,
		Point3D* target) {
	this->id = id;
	this->near = near;
	this->far = far;
	this->angle = angle;
	this->pos = pos;
	this->target = target;
}

Camera::~Camera() {

}
