#include "LinearAnimation.h"

LinearAnimation::LinearAnimation(string id, float span,
		vector<Point3D*> &controlPoints) :
		Animation(id, span) {

	this->controlPoints = controlPoints;
	this->numberOfTransitions = controlPoints.size() - 1;

	calculateDistancesBetweenControlPoints();
	calculateDirectionsBetweenControlPoints();
	this->totalDistance = getTotalDistance();
}

LinearAnimation::~LinearAnimation() {

}

void LinearAnimation::calculateDistancesBetweenControlPoints() {
	for (unsigned int i = 0; i < numberOfTransitions; i++)
		distancesBetweenControlPoints.push_back(
				getDistanceBetweenPoints((*controlPoints[i + 1]),
						(*controlPoints[i])));
}

void LinearAnimation::calculateDirectionsBetweenControlPoints() {
	for (unsigned int i = 0; i < numberOfTransitions; i++)
		directionsBetweenControlPoints.push_back(getDirectionBetweenPoints((*controlPoints[i + 1]),
						(*controlPoints[i]), distancesBetweenControlPoints[i]));
}

float LinearAnimation::getTotalDistance() {
	return 0;
}

void LinearAnimation::init() {

}

void LinearAnimation::apply() {

}

void LinearAnimation::update() {

}
