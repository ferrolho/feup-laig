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

	this->animationProgress = this->totalDistance / this->span;
	printf("\nanimationProgress: %f\n", animationProgress);
	getchar();

	this->currentPointControl = 0;
	this->currentPosition = controlPoints[0];

	this->currentRotation = calculateCurrentRotation();
	this->transition = true;
}

LinearAnimation::~LinearAnimation() {

}

void LinearAnimation::init(unsigned long sysTime) {

	isFinished = false;
	currentDistance = 0;
	currentPointControl = 0;
	currentPosition = controlPoints[0];
	currentRotation = calculateCurrentRotation();
	oldTime = sysTime;
}

void LinearAnimation::apply() {
	if (!isFinished) {
		glTranslatef(currentPosition->getX(), currentPosition->getY(),
				currentPosition->getZ());
		if (currentPointControl >= 1 && !transition) {
			glRotatef(currentRotation, 0, 1, 0);
			transition = true;
		}
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

		printf("AnimationProg: %f\n", animationProgress);
		printf("CurDistance: %f\n", currentDistance);
		currentDistance += delta;
		printf("Delta: %f\n", delta);

		if (currentDistance
				>= distancesBetweenControlPoints[currentPointControl]) {
			currentDistance -=
					distancesBetweenControlPoints[currentPointControl];

			currentPointControl = (currentPointControl + 1)
					% numberOfTransitions;
			currentPosition->setPoint(*controlPoints[currentPointControl]);
			transition = false;

			if (currentPointControl == 0) {
				if (start) {
					init(sysTime);
				} else {
					isFinished = true;
				}
			} else {
				currentRotation = calculateCurrentRotation();
				updateCurrentPosition(currentDistance);
			}
		}
	}
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
						(*controlPoints[i + 1]), distancesBetweenControlPoints[i]));
}

float LinearAnimation::getTotalDistance() {
	float total = 0;

	for (unsigned int i = 0; i < numberOfTransitions; i++) {
		total += distancesBetweenControlPoints[i];
	}

	return total;
}

float LinearAnimation::calculateCurrentRotation() {
	if (currentPointControl >= 1) {
		float angle;

		Point3D* invFirstDirection = new Point3D(
				-1.0f
						* (*directionsBetweenControlPoints[currentPointControl
								- 1]));

		Point2D* u = new Point2D(invFirstDirection->getX(),
				invFirstDirection->getZ());

		Point2D* v = new Point2D(
				directionsBetweenControlPoints[currentPointControl]->getX(),
				directionsBetweenControlPoints[currentPointControl]->getZ());

		angle = 180.0 - calculateAngleBetweenPoints(*u, *v);

		return angle;
	}

	return 0;
}

void LinearAnimation::updateCurrentPosition(float delta) {

	printf("AQUI\n");
	printf("Delta: %f\n", delta);
	printf("Angle: %f\n", currentRotation);

	Point3D p = delta * (*directionsBetweenControlPoints[currentPointControl]);
	currentPosition = new Point3D((*currentPosition) + p);

	printf("Current Point: %s\n", currentPosition->toString().c_str());
	printf("Current Direction: %s\n", directionsBetweenControlPoints[currentPointControl]->toString().c_str());
}
