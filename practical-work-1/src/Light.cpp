#include "Light.h"

int Light::nextLightID = 0;
int Light::getNextLightID() {
	return nextLightID;
}

Light::Light(bool enabled, bool marker, Point3D pos, Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZ()) {
	this->enabled = enabled;
	this->marker = marker;
	this->components = components;
}

Light::Light(string enabled, string marker, Point3D pos, Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZ()) {
	this->enabled = enabled.compare("true") == 0;
	this->marker = marker.compare("true") == 0;
	this->components = components;
}

Light::~Light() {
}

Components* Light::getComponents() {
	return components;
}

bool Light::getMarker() {
	return marker;
}

bool Light::isEnabled() {
	return enabled;
}
