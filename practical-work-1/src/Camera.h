#pragma once

#include <string>

#include "Point3D.h"

using namespace std;

class Camera {
private:
	string id;
	float near, far, angle;
	Point3D *pos, *target;

public:
	Camera(string id, float near, float far, float angle, Point3D* pos,
			Point3D* target);
	virtual ~Camera();
};
