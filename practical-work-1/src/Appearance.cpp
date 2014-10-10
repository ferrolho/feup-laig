#include "Appearance.h"

Appearance::Appearance(string id, float shininess, vector<RGBA* > reflectionValues) {
	this->id = id;
	this->shininess = shininess;
	this->refletionValues = reflectionValues;
}

Appearance::~Appearance() {

}
