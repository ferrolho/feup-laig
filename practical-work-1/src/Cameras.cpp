#include "Cameras.h"

Cameras::Cameras() {
}

Cameras::Cameras(Cameras* cameras) {
	this->cameras = cameras->cameras;
}

Cameras::~Cameras() {
}

void Cameras::init() {

}

void Cameras::update() {

}


void Cameras::draw() {

}

void Cameras::add(Camera* camera) {
		cameras.push_back(camera);
}
