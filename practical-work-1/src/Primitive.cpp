#include "Primitive.h"

Primitive::Primitive() {
	this->texture = NULL;
}

Primitive::~Primitive() {
}

void Primitive::setTexture(Texture* texture) {
	if(texture)
		this->texture = texture;
	else
		this->texture = NULL;
}
