#include "Light.h"

int Light::nextLightID = 0;
int Light::getNextLightID() {
	return nextLightID;
}

Light::Light(string strId, bool enabled, bool marker, Point3D pos,
		Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW()) {
	this->strId = strId;
	this->enabled = enabled;
	this->marker = marker;
	this->components = components;
}

Light::Light(string strId, string enabled, string marker, Point3D pos,
		Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW()) {
	this->strId = strId;
	this->enabled = enabled.compare("true") == 0;
	this->marker = marker.compare("true") == 0;
	this->components = components;
}

Light::Light(string strId, bool enabled, bool marker, Point3D pos,
		Point3D target, Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW(), target.getXYZ()) {
	this->strId = strId;
	this->enabled = enabled;
	this->marker = marker;
	this->components = components;
}

Light::Light(string strId, string enabled, string marker, Point3D pos,
		Point3D target, Components* components) :
		CGFlight(GL_LIGHT0 + nextLightID++, pos.getXYZW(), target.getXYZ()) {
	this->strId = strId;
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
	if (enabled) {
		glEnable(id);
		CGFlight::update();
	} else
		glDisable(id);
}

void Light::draw() {
	if (enabled && marker)
		CGFlight::draw();
}

Components* Light::getComponents() {
	return components;
}

int* Light::getEnabled() {
	return &enabled;
}

GLenum Light::getID() {
	return id;
}

bool Light::getMarker() {
	return marker;
}

string Light::getStrID() {
	return strId;
}

bool Light::isEnabled() {
	return enabled;
}
