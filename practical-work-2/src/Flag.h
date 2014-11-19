#pragma once

#include "Primitive.h"
#include "Texture.h"

class Flag: public Primitive {
private:

	Texture *texture;

public:
	Flag(Texture* texture);
	virtual ~Flag();

	void draw();
	void updateTexture(Texture* texture);
};




