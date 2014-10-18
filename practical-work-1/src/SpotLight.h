#pragma once

#include <string>
#include "Components.h"
#include "Light.h"
#include "Point3D.h"
using namespace std;

class SpotLight: public Light {
private:
	float angle, exponent;

public:
	SpotLight(bool enabled, bool marker, Point3D pos, Point3D target,
			float angle, float exponent, Components* components);
	SpotLight(string enabled, string marker, Point3D pos, Point3D target,
			float angle, float exponent, Components* components);
	virtual ~SpotLight();

	void init();
};
