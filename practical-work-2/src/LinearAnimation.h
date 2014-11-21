#pragma once

#include <vector>

#include "Animation.h"
#include "Point3D.h"

class LinearAnimation: public Animation {
private:
	unsigned int currentControlPoint;
	vector<Point3D*> controlPoints;
	unsigned int numberOfTransitions;

	float currentDistance, totalDistance;
	vector<float> distancesBetweenControlPoints;
	vector<Point3D*> directionsBetweenControlPoints;

	float v;
	Point3D* currentPosition;
	float currentRotation;
	float distanceFromStartToNextControlPoint;

public:
	LinearAnimation(string id, float span, vector<Point3D*>& controlPoints);
	virtual ~LinearAnimation();

	void restart();
	void update(unsigned long sysTime);
	void apply();

	void calculateDistancesBetweenControlPoints();
	void calculateDirectionsBetweenControlPoints();
	float getTotalDistance();
	float calculateCurrentRotation();
	void updateCurrentPosition(float delta);
};
