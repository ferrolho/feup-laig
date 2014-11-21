#include "LinearAnimation.h"

#include <stdio.h>

LinearAnimation::LinearAnimation(string id, float span,
		vector<Point3D*> &controlPoints) :
		Animation(id, span) {

	this->controlPoints = controlPoints;
	this->numberOfTransitions = controlPoints.size() - 1;

	calculateDistancesBetweenControlPoints();
	calculateDirectionsBetweenControlPoints();
	this->totalDistance = getTotalDistance();
	this->nextDistance = distancesBetweenControlPoints[0];

	this->animationProgress = this->totalDistance / this->span;

	this->currentPointControl = 0;
	this->currentPosition = controlPoints[0];

	this->currentRotation = calculateCurrentRotation();
}

LinearAnimation::~LinearAnimation() {

}

void LinearAnimation::init(unsigned long sysTime) {

	isFinished = false;
	currentDistance = 0;
	this->nextDistance = distancesBetweenControlPoints[0];
	currentPointControl = 0;
	currentPosition = controlPoints[0];
	currentRotation = calculateCurrentRotation();
	oldTime = sysTime;
}

void LinearAnimation::apply() {
	if (!isFinished) {
		glTranslatef(currentPosition->getX(), currentPosition->getY(),
				currentPosition->getZ());
		glRotatef(currentRotation, 0, 1, 0);
		//printf("\nEntrou no Apply!\n");
	}
}

void LinearAnimation::update(unsigned long sysTime) {
	if (start) {
		init(sysTime);
		start = false;
	} else if (!isFinished) {
		float deltaTime = (sysTime - oldTime) * 0.001;
		this->oldTime = sysTime;

		float delta = this->animationProgress * deltaTime;

		updateCurrentPosition(delta);
		currentDistance += delta;

		if (currentDistance >= nextDistance) {
			printf("\nChanged Point!\n");

			currentPointControl = (currentPointControl + 1)
					% numberOfTransitions;

			nextDistance += distancesBetweenControlPoints[currentPointControl];
			currentPosition->setPoint(*controlPoints[currentPointControl]);

			if (currentPointControl == 0)
				isFinished = true;
			else {
				printf("Current Point Control: %u\nENTROU\n",
						currentPointControl);
				currentRotation += calculateCurrentRotation();
				printf("Current Rotation: %f\n", currentRotation);
			}
		}
	}

	/*printf("%s %s %s %f", currentPosition->toString().c_str(),
	 controlPoints[currentPointControl]->toString().c_str(),
	 directionsBetweenControlPoints[currentPointControl]->toString().c_str(),
	 currentRotation);*/

}

void LinearAnimation::calculateDistancesBetweenControlPoints() {
	for (unsigned int i = 0; i < numberOfTransitions; i++)
		distancesBetweenControlPoints.push_back(
				getDistanceBetweenPoints((*controlPoints[i + 1]),
						(*controlPoints[i])));
}

void LinearAnimation::calculateDirectionsBetweenControlPoints() {
	for (unsigned int i = 0; i < numberOfTransitions; i++)
		directionsBetweenControlPoints.push_back(
				getDirectionBetweenPoints((*controlPoints[i]),
						(*controlPoints[i + 1]),
						distancesBetweenControlPoints[i]));
}

float LinearAnimation::getTotalDistance() {
	float total = 0;

	for (unsigned int i = 0; i < numberOfTransitions; i++) {
		total += distancesBetweenControlPoints[i];
	}

	return total;
}

float LinearAnimation::calculateCurrentRotation() {
	if (currentPointControl != 0) {
		Point3D* u = new Point3D(
				*directionsBetweenControlPoints[currentPointControl - 1]);

		printf("\nFirst Point: %s\n", u->toString().c_str());

		Point3D* v = directionsBetweenControlPoints[currentPointControl];

		printf("\nSecond Point: %s\n", v->toString().c_str());

		printf("\nAngle: %f\n", calculateAngleBetweenPoints(*u, *v));

		return (180.0 - calculateAngleBetweenPoints(*u, *v));
	}

	return 45.0;
}

void LinearAnimation::updateCurrentPosition(float delta) {
	Point3D p = delta * (*directionsBetweenControlPoints[currentPointControl]);
	currentPosition = new Point3D((*currentPosition) + p);
}
