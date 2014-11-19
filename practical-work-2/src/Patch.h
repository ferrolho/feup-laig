#pragma once

#include <string>
#include "Primitive.h"
#include "Texture.h"

class Patch: public Primitive {
private:
	int order, partsU, partsV;
	int uStride, vStride;
	string compute;
	float* controlPoints;
	Texture *texture;

public:
	Patch(int order, int partsU, int partsV, string compute,
			float* controlPoints, Texture* texture);
	virtual ~Patch();

	void draw();
	void updateTexture(Texture* texture);
};
