#include "Animation.h"

Animation::Animation(string id, float span) {
	this->id = id;
	this->span = span;

	lastTime = 0;
	running = false;
	done = true;
	orientation = true;
}

Animation::~Animation() {
}

void Animation::restart() {
	lastTime = 0;
	done = false;
	running = true;
}

string Animation::getId() {
	return id;
}

bool Animation::isDone() {
	return done;
}

bool Animation::isRunning() {
	return running;
}

bool Animation::isOrientable() {
	return orientation;
}

void Animation::setOrientation(bool orientation) {
	this->orientation = orientation;
}

CircularAnimation::CircularAnimation(string id, float span, Point3D* center,
		float radius, float startAngle, float rotAngle, RefPlane plane) :
		Animation(id, span) {
	this->center = center;
	this->radius = radius;
	this->startAng = startAngle;
	this->rotAng = rotAngle;
	this->plane = plane;

	endAng = startAng + rotAng;
	ang = startAng;
	w = rotAng / span;
}

CircularAnimation::~CircularAnimation() {
}

void CircularAnimation::resetValues() {
	ang = startAng;
}

void CircularAnimation::restart() {
	Animation::restart();
	resetValues();
}

void CircularAnimation::update(unsigned long time) {
	if (!done) {
		// first animation iteration
		if (!lastTime)
			lastTime = time;
		else {
			float deltaTime = (time - lastTime) * 0.001;
			lastTime = time;

			ang += w * deltaTime;

			if (abs(ang) >= abs(endAng))
				done = true;
		}
	}
}

void CircularAnimation::apply() {
	glTranslatef(center->getX(), center->getY(), center->getZ());
	if (plane == XZ) {
		glTranslatef(radius * sin(degToRad(ang)), 0,
				radius * cos(degToRad(ang)));
		glRotatef(ang, 0, 1, 0);
	} else if (plane == YZ) {
		glTranslatef(0, radius * sin(degToRad(ang)),
				radius * cos(degToRad(ang)));
		glRotatef(ang, 1, 0, 0);
	}
}

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

void LinearAnimation::resetValues() {
	currentDistance = 0;
	this->distanceFromStartToNextControlPoint =
			distancesBetweenControlPoints[0];

	currentControlPoint = 0;
	currentPosition = controlPoints[0];

	currentRotation = calculateCurrentRotation();
}

void LinearAnimation::restart() {
	Animation::restart();
	resetValues();
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

				if (currentControlPoint != 0)
					currentPosition->setPoint(
							*controlPoints[currentControlPoint]);

				if (currentControlPoint == 0)
					done = true;
				else {
					if (orientation)
						currentRotation += calculateCurrentRotation();
				}
			}
		}
	}
}

void LinearAnimation::apply() {
	glTranslatef(currentPosition->getX(), currentPosition->getY(),
			currentPosition->getZ());
	glRotatef(currentRotation, 0, 1, 0);
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
