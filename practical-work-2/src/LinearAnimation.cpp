#include "LinearAnimation.h"

LinearAnimation::LinearAnimation(string id, float span,
		vector<Point3D*> &controlPoints) :
		Animation(id, span) {

	this->controlPoints = controlPoints;
}

LinearAnimation::~LinearAnimation() {

}

Point3D* LinearAnimation::processTransformations() {
	// TODO think in a process to cases when we have more than 2 control points
	return NULL;
}
