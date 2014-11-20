#include "CircularAnimation.h"

#include <stdio.h>

CircularAnimation::CircularAnimation(string id, float span, Point3D* center,
		float radius, float startAngle, float rotAngle) :
		Animation(id, span) {
	this->center = center;
	this->radius = radius;
	this->startAngle = startAngle;
	this->rotAngle = rotAngle;
	endAngle = startAngle + rotAngle;

	this->w = rotAngle / span;
	this->angle = startAngle;
}

CircularAnimation::~CircularAnimation() {
}

void CircularAnimation::init(unsigned long sysTime) {
	angle = startAngle;

	oldTime = sysTime;
	time = 0;
}

void CircularAnimation::update(unsigned long sysTime) {
	if (start) {
		init(sysTime);
		start = false;
	} else if (!isFinished) {
		float deltaTime = (sysTime - oldTime) * 0.001;
		this->oldTime = sysTime;

		angle += w * deltaTime;

		printf("%f %f %f\n", startAngle, angle, endAngle);
		if (abs(angle) >= abs(endAngle))
			isFinished = true;
	}
}

void CircularAnimation::apply() {
	if (!isFinished) {
		glTranslatef(radius * sin(degToRad(angle)), 0,
				radius * cos(degToRad(angle)));
		glRotatef(angle, 0, 1, 0);
		glTranslatef(-radius, 0, 0);
	}
}
