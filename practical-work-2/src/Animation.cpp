#include "Animation.h"

Animation::Animation(string id, float span) {
	this->id = id;
	this->span = span;

	lastTime = 0;
	done = true;
}

Animation::~Animation() {
}

void Animation::restart() {
	lastTime = 0;
	done = false;
}

string Animation::getId() {
	return id;
}

CircularAnimation::CircularAnimation(string id, float span, Point3D* center,
		float radius, float startAngle, float rotAngle) :
		Animation(id, span) {
	this->center = center;
	this->radius = radius;
	this->startAng = startAngle;
	this->rotAng = rotAngle;

	endAng = startAng + rotAng;
	ang = startAng;
	w = rotAng / span;
}

CircularAnimation::~CircularAnimation() {
}

void CircularAnimation::restart() {
	Animation::restart();
	ang = startAng;
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
	if (!done) {
		glTranslatef(center->getX(), center->getY(), center->getZ());
		glTranslatef(radius * sin(degToRad(ang)), 0,
				radius * cos(degToRad(ang)));
		glRotatef(ang, 0, 1, 0);
	}
}
