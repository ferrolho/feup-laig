#pragma once

#include "CGFlight.h"
#include "Components.h"
#include "Point3D.h"
using namespace std;

class Light: public CGFlight {
private:
	static int nextLightID;

	bool enabled, marker;
	Components* components;

public:
	static int getNextLightID();

	Light(bool enabled, bool marker, Point3D pos, Components* components);
	Light(string enabled, string marker, Point3D pos, Components* components);
	virtual ~Light();

	Components* getComponents();
	bool getMarker();
	bool isEnabled();
};
