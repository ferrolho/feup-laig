#pragma once

#include <string>
#include "CGFcamera.h"

using namespace std;

class Camera: public CGFcamera {
protected:
	string id;
	float near, far;

public:
	Camera(string id, float near, float far);
	virtual ~Camera();

	string getId();
	/*
	 float getNear();
	 float getFar();
	 */
};
