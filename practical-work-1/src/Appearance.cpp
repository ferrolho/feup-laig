#include "Appearance.h"

Appearance::Appearance(const string& id, float shininess, Texture* texture,
		const vector<RGBA*>& components) :
		CGFappearance() {
	this->id = id;
	this->texture = texture;

	RGBA* ambRGBA = components[0];
	float amb[4] = { ambRGBA->getR(), ambRGBA->getG(), ambRGBA->getB(),
			ambRGBA->getA() };

	RGBA* difRGBA = components[1];
	float dif[4] = { difRGBA->getR(), difRGBA->getG(), difRGBA->getB(),
			difRGBA->getA() };

	RGBA* specRGBA = components[2];
	float spec[4] = { specRGBA->getR(), specRGBA->getG(), specRGBA->getB(),
			specRGBA->getA() };

	setAmbient(amb);
	setDiffuse(dif);
	setSpecular(spec);
	setShininess(shininess);

	if (texture) {
		setTexture(texture->getFilepath());
		setTextureWrap(GL_REPEAT, GL_REPEAT);
	}
}

Appearance::~Appearance() {
}

string Appearance::getId() {
	return id;
}
