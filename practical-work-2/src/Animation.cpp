#include "Animation.h"

Animation::Animation(string id, float span) {
	this->id = id;
	this->span = span;

	this->currentPosition = NULL;
	this->isFinished = false;
}

Animation::~Animation() {

}

string Animation::getId() {
	return id;
}

Point3D* Animation::getCurrentPosition() {
	return currentPosition;
}
