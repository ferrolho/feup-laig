#include "Animation.h"

Animation::Animation(string id, float span) {
	this->id = id;
	this->span = span;
}

Animation::~Animation() {

}

string Animation::getId() {
	return id;
}
