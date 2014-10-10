#include "Appearance.h"

Appearance::Appearance(string id, float shininess, string textureRef, vector<RGBA* > reflectionValues) {
	this->id = id;
	this->shininess = shininess;
	this->textureRef = textureRef;
	this->refletionValues = reflectionValues;
}

Appearance::~Appearance() {

}
