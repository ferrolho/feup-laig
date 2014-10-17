#pragma once

#include "PrimitiveType.h"
#include "Texture.h"

class Primitive {
private:
	PrimitiveType type;

protected:
	Texture* texture;

public:
	Primitive(PrimitiveType type);
	virtual ~Primitive();

	virtual void draw() = 0;
	void setTexture(Texture* texture);
	PrimitiveType getType();
};
