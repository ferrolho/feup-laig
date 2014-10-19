#pragma once

#include "Camera.h"
#include "Point3D.h"
#include <CGFapplication.h>

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

	void applyView();
	void updateProjectionMatrix(int width, int height);

	bool rotateTo(int axis, float angle, float increment);
	bool rotate(int axis, float angle);
	bool setRotation(int axis, float angle);
	bool moveTo(int axis, float value, float increment);
	bool translate(int axis, float value);
};
