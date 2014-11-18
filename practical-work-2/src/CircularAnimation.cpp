#include "CircularAnimation.h"

CircularAnimation::CircularAnimation(string id, float span, Point3D* center,
		float radius, float startAngle, float rotAngle) :
		Animation(id, span) {

	this->center = center;
	this->radius = radius;
	this->startAngle = startAngle;
	this->rotAngle = rotAngle;
}

CircularAnimation::~CircularAnimation() {

}
