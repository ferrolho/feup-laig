#include "Texture.h"

Texture::Texture(const Texture* texture) {
	id = texture->id;
	file = texture->file;
	texLenghtS = texture->texLenghtS;
	texLenghtT = texture->texLenghtT;
}

Texture::Texture(const string& id, const string& file, float texLenght_s,
		float texLenght_t) :
		CGFtexture(file) {
	this->id = id;
	this->file = file;
	this->texLenghtS = texLenght_s;
	this->texLenghtT = texLenght_t;
}

Texture::~Texture() {
}

const string Texture::getId() {
	return id;
}

const string Texture::getFilepath() {
	return file;
}

const float Texture::getTexLenght_s() {
	return texLenghtS;
}

const float Texture::getTexLenght_t() {
	return texLenghtT;
}
