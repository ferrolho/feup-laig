#include "Cameras.h"

Cameras::Cameras() {
}

Cameras::Cameras(Cameras* cameras) {
	this->cameras = cameras->cameras;
	this->activedCamera = cameras->getActivedCamera();
}

Cameras::~Cameras() {

}

void Cameras::add(Camera* camera) {
	cameras[camera->getId()] = camera;
}

map<string, Camera*>* Cameras::getCameras() {
	return &cameras;
}

string Cameras::getActivedCamera() {
	return activedCamera;
}

void Cameras::setActivedCamera(string newCamera) {
	this->activedCamera = newCamera;
}
