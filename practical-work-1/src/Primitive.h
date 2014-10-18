#pragma once

#include "Texture.h"

class Primitive {
public:
	Primitive();
	virtual ~Primitive();

	virtual void draw() = 0;
	virtual void updateTexture(Texture* texture);
};
