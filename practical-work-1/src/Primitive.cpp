#include "Primitive.h"

Primitive::Primitive(PrimitiveType type) {
	this->type = type;
}

Primitive::~Primitive() {
}

PrimitiveType Primitive::getType() {
	return type;
}
