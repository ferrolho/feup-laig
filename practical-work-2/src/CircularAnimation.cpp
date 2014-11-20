#include "CircularAnimation.h"

#include <stdio.h>

CircularAnimation::CircularAnimation(string id, float span, Point3D* center,
		float radius, float startAngle, float rotAngle) :
		Animation(id, span) {

	this->center = center;
	this->radius = radius;
	this->startAngle = startAngle;
	this->rotAngle = rotAngle;

	this->angularVelocity = (rotAngle / span);
	this->currentRotation = startAngle;
}

CircularAnimation::~CircularAnimation() {

}

void CircularAnimation::setCurrentPosition() {
	float angle = startAngle + currentRotation;

	float x = center->getX() + radius * cos(degToRad(angle));
	float y = center->getY();
	float z = center->getZ() + radius * sin(degToRad(angle));

	currentPosition = new Point3D(x, y, z);
	printf("AQUI\n");
}

void CircularAnimation::init(unsigned long sysTime) {
	currentRotation = startAngle;

	setCurrentPosition();

	oldTime = sysTime;

	time = 0;
}

void CircularAnimation::update(unsigned long sysTime) {

	if (start) {
		init(sysTime);
		start = false;
	} else {
		if (!isFinished) {
			float deltaTime = (sysTime - oldTime) * 0.001;
			this->oldTime = sysTime;

			printf("currentRotation: %f\n", currentRotation);
			printf("currentPosition: %s\n", currentPosition->toString().c_str());
			printf("time: %f\n", time);
			printf("radius: %f\n", radius);
			time += deltaTime;

			currentRotation += angularVelocity * deltaTime;

			setCurrentPosition();

			if (abs(currentRotation) >= abs(startAngle + rotAngle)) {
				if (start) {
					init(sysTime);
				} else {
					isFinished = true;
				}
			}
		}
	}
}

void CircularAnimation::apply() {
	if (!isFinished) {
		glRotatef(currentRotation, 0, 1, 0);
		glTranslatef(currentPosition->getX(), 0, currentPosition->getZ());
	}
}
