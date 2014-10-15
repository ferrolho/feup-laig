#pragma once

#include "RGBA.h"

class Components {
private:
	RGBA *ambient, *diffuse, *specular;

public:
	Components(RGBA* ambient, RGBA* diffuse, RGBA* specular);
	virtual ~Components();

	float* getAmbient();
	float* getDiffuse();
	float* getSpecular();
};
