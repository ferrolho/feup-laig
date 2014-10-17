#include "Primitive.h"

Primitive::Primitive(PrimitiveType type) {
	this->type = type;
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

PrimitiveType Primitive::getType() {
	return type;
}
