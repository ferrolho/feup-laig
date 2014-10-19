#pragma once

#include "Camera.h"
#include "CGFapplication.h"

class Ortho: public Camera {
private:
	char direction;
	float left, right, top, bottom;

public:
	Ortho(string id, float near, float far, char direction, float left,
			float right, float top, float bottom);
	virtual ~Ortho();

	void applyView();
	void updateProjectionMatrix();

	/*
	 char getDirection();
	 float getRight();
	 float getLeft();
	 float getTop();
	 float getBottom();
	 */
};
