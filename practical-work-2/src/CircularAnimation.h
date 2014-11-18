#pragma once

#include "Animation.h"
#include "Point3D.h"

class CircularAnimation: public Animation {
private:
	Point3D* center;
	float radius, startAngle, rotAngle;

public:
	CircularAnimation(string id, float span, Point3D* center, float radius,
			float startAngle, float rotAngle);
	virtual ~CircularAnimation();
};
