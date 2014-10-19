#include "Camera.h"

Camera::Camera(string id, float near, float far) :
		CGFcamera() {
	this->id = id;
	this->near = near;
	this->far = far;
}

Camera::~Camera() {
}

string Camera::getId() {
	return id;
}

/*
 float Camera::getNear() {
 return near;
 }

 float Camera::getFar() {
 return far;
 }
 */
