#include "Texture.h"

Texture::Texture(const string& id, const string& file, float texLenght_s,
		float texLenght_t)  : CGFtexture(file) {
	this->id = id;
	this->file = file;
	this->texLenght_s = texLenght_s;
	this->texLenght_t = texLenght_t;
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
	return texLenght_s;
}

const float Texture::getTexLenght_t() {
	return texLenght_t;
}
