#pragma once

#include "Animation.h"
#include "Point3D.h"

class CircularAnimation: public Animation {
private:
	Point3D* center;
	float radius, startAngle, rotAngle;

	float currentRotation;
	float angularVelocity;
	float time;

public:
	CircularAnimation(string id, float span, Point3D* center, float radius,
			float startAngle, float rotAngle);
	virtual ~CircularAnimation();

	void setCurrentPosition();

	void init(unsigned long sysTime);
	void update(unsigned long sysTime);
	void apply();
};
