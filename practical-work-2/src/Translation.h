#pragma once

#include "Point3D.h"
#include "Transform.h"

class Translation: public Transform {
private:
	Point3D to;

public:
	Translation(Point3D to);
	virtual ~Translation();

	void apply();
};
