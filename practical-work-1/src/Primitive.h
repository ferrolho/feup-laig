#pragma once

#include "PrimitiveType.h"

class Primitive {
private:
	PrimitiveType type;

public:
	Primitive(PrimitiveType type);
	virtual ~Primitive();

	virtual void draw() = 0;
	PrimitiveType getType();
};
