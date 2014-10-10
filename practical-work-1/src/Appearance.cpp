#include "Appearance.h"

Appearance::Appearance(const string& id, float shininess,
		const string& textureRef, const vector<RGBA*>& components) {
	this->id = id;
	this->shininess = shininess;
	this->textureRef = textureRef;
	this->components = components;
}

Appearance::~Appearance() {
}
