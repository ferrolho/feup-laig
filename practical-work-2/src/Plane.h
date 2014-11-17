#pragma once

#include "Primitive.h"

class Plane: public Primitive {
public:
	Plane(unsigned int divisions);
	virtual ~Plane();

	void draw();
	//void updateTexture(Texture* texture);

private:
	unsigned int divisions;
	CGFtexture *myTexture;
};
