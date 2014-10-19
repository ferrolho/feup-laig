#pragma once

#include "Camera.h"
#include "CGFapplication.h"
#include "Point3D.h"

class Perspective: public Camera {
private:
	float angle;
	Point3D *pos, *target;

public:
	Perspective(string id, float near, float far, float angle, Point3D* pos,
			Point3D* target);
	virtual ~Perspective();

	 void applyView();
	 void updateProjectionMatrix(int width, int height);

	/*
	 float getAngle();
	 Point3D* getPos();
	 Point3D* getTarget();

	 bool rotateTo(int axis, float angle, float increment);
	 bool rotate(int axis, float angle);
	 bool setRotation(int axis, float angle);
	 bool moveTo(int axis, float value, float increment);
	 bool translate(int axis, float value);
	 */
};
