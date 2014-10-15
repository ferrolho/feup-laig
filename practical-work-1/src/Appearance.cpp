#include "Appearance.h"

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
	if(texture)
		return texture;
	else
		return NULL;
}
