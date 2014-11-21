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
	unsigned int currentPointControl;
	float totalDistance;
	float animationProgress;
	Point3D* currentPosition;
	float currentRotation;
	float currentDistance;
	float nextDistance;

public:
	LinearAnimation(string id, float span, vector<Point3D*>& controlPoints);
	virtual ~LinearAnimation();

	void restart();
	void apply();
	void update(unsigned long sysTime);

	void calculateDistancesBetweenControlPoints();
	void calculateDirectionsBetweenControlPoints();
	float getTotalDistance();
	float calculateCurrentRotation();
	void updateCurrentPosition(float delta);

};
