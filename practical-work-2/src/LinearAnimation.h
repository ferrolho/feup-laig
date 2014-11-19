#pragma once

#include <vector>

#include "Animation.h"
#include "Point3D.h"

class LinearAnimation: public Animation {
private:
	vector<Point3D*> controlPoints;
	vector<float> distancesBetweenControlPoints;
	vector<Point3D*> directionsBetweenControlPoints;
	unsigned int numberOfTransitions;
	float totalDistance;

public:
	LinearAnimation(string id, float span, vector<Point3D*>& controlPoints);
	virtual ~LinearAnimation();

	void calculateDistancesBetweenControlPoints();
	void calculateDirectionsBetweenControlPoints();
	float getTotalDistance();

	void init();
	void apply();
	void update();
};
