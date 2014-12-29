#pragma once

#include <string>
#include "CGFapplication.h"
#include "Utilities.h"

using namespace std;

class Animation {
protected:
	string id;
	float span;
	bool running, done, orientation;
	unsigned long lastTime;

public:
	Animation(string id, float span);
	virtual ~Animation();

	virtual void resetValues() = 0;
	virtual void restart();
	virtual void update(unsigned long sysTime) = 0;
	virtual void apply() = 0;

	string getId();
	bool isDone();
	bool isRunning();
	bool isOrientable();
	void setOrientation(bool orientation);
};

class CircularAnimation: public Animation {
private:
	Point3D* center;
	float radius, startAng, rotAng, endAng, ang, w;

public:
	CircularAnimation(string id, float span, Point3D* center, float radius,
			float startAngle, float rotAngle);
	virtual ~CircularAnimation();

	void resetValues();
	void restart();
	void update(unsigned long time);
	void apply();
};

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

	void resetValues();
	void restart();
	void update(unsigned long sysTime);
	void apply();

	void calculateDistancesBetweenControlPoints();
	void calculateDirectionsBetweenControlPoints();
	float getTotalDistance();
	float calculateCurrentRotation();
	void updateCurrentPosition(float delta);
};
