#pragma once

#include "PrimitiveType.h"

class Primitive {
private:
	PrimitiveType type;

public:
	Primitive(PrimitiveType type);
	virtual ~Primitive();

	PrimitiveType getType();
};
