#include "Cameras.h"

Cameras::Cameras() {
}

Cameras::Cameras(Cameras* cameras) {
	this->cameras = cameras->cameras;
	this->activeCamera = cameras->getActiveCameraID();
}

Cameras::~Cameras() {
}

void Cameras::add(Camera* camera) {
	cameras[camera->getId()] = camera;
}

string Cameras::getActiveCameraID() {
	return activeCamera;
}

Camera* Cameras::getActiveCamera() {
	return cameras[activeCamera];
}

map<string, Camera*>* Cameras::getCameras() {
	return &cameras;
}

void Cameras::setActiveCameraID(string camera) {
	this->activeCamera = camera;
}
