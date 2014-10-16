#pragma once

#include "Camera.h"

class Ortho: public Camera {

private:
	char direction;
	float left, right, top, bottom;

public:
	Ortho();
	Ortho(Ortho* ortho);
	Ortho(string id, float near, float far, char direction, float left,
			float right, float top, float bottom);
	virtual ~Ortho();

	char getDirection();
	float getRight();
	float getLeft();
	float getTop();
	float getBottom();
};
