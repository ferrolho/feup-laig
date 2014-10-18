#include <src/Camera.h>

Camera::Camera() {
	this->id = "default";
	this->near = 1.0;
	this->far = 10.0;
}

Camera::Camera(Camera* camera) {
	this->id = camera->id;
	this->near = camera->near;
	this->far = camera->far;
}

Camera::Camera(string id, float near, float far) {
	this->id = id;
	this->near = near;
	this->far = far;
}

Camera::~Camera() {

}

string Camera::getId() {
	return id;
}

float Camera::getNear() {
	return near;
}

float Camera::getFar() {
	return far;
}
