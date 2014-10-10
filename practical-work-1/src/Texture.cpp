#include "Texture.h"

Texture::Texture(string id, string file, float texLenght_s, float texLenght_t) {
	this->id = id;
	this->file = file;
	this->texLenght_s = texLenght_s;
	this->texLenght_t = texLenght_t;
}

Texture::~Texture() {

}
