#pragma once

#include "Point3D.h"
#include "Transform.h"

class Scaling: public Transform {
private:
	Point3D factor;

public:
	Scaling(Point3D factor);
	virtual ~Scaling();

	void apply();
};
