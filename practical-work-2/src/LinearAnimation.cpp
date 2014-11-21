#include "LinearAnimation.h"

LinearAnimation::LinearAnimation(string id, float span,
		vector<Point3D*> &controlPoints) :
		Animation(id, span) {
	this->controlPoints = controlPoints;
	this->numberOfTransitions = controlPoints.size() - 1;

	calculateDistancesBetweenControlPoints();
	calculateDirectionsBetweenControlPoints();
	this->totalDistance = getTotalDistance();
	this->distanceFromStartToNextControlPoint =
			distancesBetweenControlPoints[0];

	currentDistance = 0;
	this->v = this->totalDistance / this->span;

	this->currentControlPoint = 0;
	this->currentPosition = controlPoints[0];

	this->currentRotation = calculateCurrentRotation();
}

LinearAnimation::~LinearAnimation() {
}

void LinearAnimation::restart() {
	Animation::restart();

	currentDistance = 0;
	this->distanceFromStartToNextControlPoint =
			distancesBetweenControlPoints[0];

	currentControlPoint = 0;
	currentPosition = controlPoints[0];

	currentRotation = calculateCurrentRotation();
}

void LinearAnimation::update(unsigned long time) {
	if (!done) {
		// first animation iteration
		if (!lastTime)
			lastTime = time;
		else {
			float deltaTime = (time - lastTime) * 0.001;
			lastTime = time;

			float positionInc = this->v * deltaTime;

			updateCurrentPosition(positionInc);
			currentDistance += positionInc;

			if (currentDistance >= distanceFromStartToNextControlPoint) {
				currentControlPoint = (currentControlPoint + 1)
						% numberOfTransitions;

				distanceFromStartToNextControlPoint +=
						distancesBetweenControlPoints[currentControlPoint];
				currentPosition->setPoint(*controlPoints[currentControlPoint]);

				currentControlPoint == 0 ? done = true : currentRotation +=
													calculateCurrentRotation();
			}
		}
	}
}

void LinearAnimation::apply() {
	if (!done) {
		glTranslatef(currentPosition->getX(), currentPosition->getY(),
				currentPosition->getZ());
		glRotatef(currentRotation, 0, 1, 0);
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
						(*controlPoints[i + 1]),
						distancesBetweenControlPoints[i]));
}

float LinearAnimation::getTotalDistance() {
	float total = 0;
	for (unsigned int i = 0; i < numberOfTransitions; i++)
		total += distancesBetweenControlPoints[i];

	return total;
}

float LinearAnimation::calculateCurrentRotation() {
	if (!currentControlPoint)
		return 0;

	Point3D* u = new Point3D(
			*directionsBetweenControlPoints[currentControlPoint - 1]);
	Point3D* v = directionsBetweenControlPoints[currentControlPoint];

	return calculateAngleBetween(*u, *v);
}

void LinearAnimation::updateCurrentPosition(float positionInc) {
	Point3D p = positionInc
			* (*directionsBetweenControlPoints[currentControlPoint]);
	currentPosition = new Point3D((*currentPosition) + p);
}
