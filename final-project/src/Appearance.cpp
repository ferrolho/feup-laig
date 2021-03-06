#include "Appearance.h"

Appearance::Appearance() {
	id = "default-appearance";
	texture = NULL;

	Components* components = new Components();
	setAmbient(components->getAmbient());
	setDiffuse(components->getDiffuse());
	setSpecular(components->getSpecular());
	setShininess(20);
}

Appearance::Appearance(const Appearance* appearance) {
	id = appearance->id;
	texture = appearance->texture;
}

Appearance::Appearance(const string& id, float shininess, Texture* texture,
		Components* components) :
		CGFappearance() {
	this->id = id;
	this->texture = texture;

	setAmbient(components->getAmbient());
	setDiffuse(components->getDiffuse());
	setSpecular(components->getSpecular());
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

Texture* Appearance::getTexture() {
	return texture ? texture : NULL;
}
