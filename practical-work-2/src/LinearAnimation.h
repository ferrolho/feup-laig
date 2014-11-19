#pragma once

#include "Animation.h"
#include "Point3D.h"
#include <vector>

class LinearAnimation: public Animation {
private:
	vector<Point3D*> controlPoints;

public:
	LinearAnimation(string id, float span, vector<Point3D*>& controlPoints);
	virtual ~LinearAnimation();

	Point3D* processTransformations();
};
