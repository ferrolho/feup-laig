#include "Light.h"

int Light::nextLightID = 0;
int Light::getNextLightID() {
	return nextLightID;
}

Light::Light(bool enabled, bool marker, Point3D pos, Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW()) {
	this->enabled = enabled;
	this->marker = marker;
	this->components = components;
}

Light::Light(string enabled, string marker, Point3D pos, Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW()) {
	this->enabled = enabled.compare("true") == 0;
	this->marker = marker.compare("true") == 0;
	this->components = components;
}

Light::Light(bool enabled, bool marker, Point3D pos, Point3D target,
		Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW(), target.getXYZ()) {
	this->enabled = enabled;
	this->marker = marker;
	this->components = components;
}

Light::Light(string enabled, string marker, Point3D pos, Point3D target,
		Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW(), target.getXYZ()) {
	this->enabled = enabled.compare("true") == 0;
	this->marker = marker.compare("true") == 0;
	this->components = components;
}

Light::~Light() {
}

void Light::init() {
	setAmbient(getComponents()->getAmbient());
	setDiffuse(getComponents()->getDiffuse());
	setSpecular(getComponents()->getSpecular());
}

void Light::update() {
	if (enabled)
		CGFlight::update();
}

void Light::draw() {
	if (marker)
		CGFlight::draw();
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
