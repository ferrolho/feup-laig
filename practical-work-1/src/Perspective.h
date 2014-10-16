#pragma once

#include "Camera.h"
#include "Point3D.h"

class Perspective: public Camera {

private:
	float angle;
	Point3D *pos, *target;

public:
	Perspective();
	Perspective(Perspective* perspective);
	Perspective(string id, float near, float far, float angle, Point3D* pos,
			Point3D* target);
	virtual ~Perspective();

	float getAngle();
	Point3D* getPos();
	Point3D* getTarget();

};
