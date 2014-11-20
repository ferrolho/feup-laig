#include "Animation.h"

Animation::Animation(string id, float span) {
	this->id = id;
	this->span = span;

	this->currentPosition = NULL;
	this->oldTime = 0;
	this->start = true;
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

void Animation::reset() {
	start = true;
	isFinished = false;
}
