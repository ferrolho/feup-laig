#pragma once

#include "Primitive.h"
#include "Texture.h"

class Plane: public Primitive {
private:
	unsigned int parts;
	Texture *texture;

public:
	Plane(unsigned int parts, Texture* texture);
	virtual ~Plane();

	void draw();
	void updateTexture(Texture* texture);
};
