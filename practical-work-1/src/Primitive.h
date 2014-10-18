#pragma once

#include "Texture.h"

class Primitive {
protected:
	Texture* texture;

public:
	Primitive();
	virtual ~Primitive();

	virtual void draw() = 0;
	void setTexture(Texture* texture);
};
