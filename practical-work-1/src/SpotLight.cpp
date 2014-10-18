#include "SpotLight.h"

#include "CGFapplication.h"

SpotLight::SpotLight(bool enabled, bool marker, Point3D pos, Point3D target,
		float angle, float exponent, Components* components) :
		Light(enabled, marker, pos, target, components) {
	this->angle = angle;
	this->exponent = exponent;
}

SpotLight::SpotLight(string enabled, string marker, Point3D pos, Point3D target,
		float angle, float exponent, Components* components) :
		Light(enabled, marker, pos, target, components) {
	this->angle = angle;
	this->exponent = exponent;
}

SpotLight::~SpotLight() {
}

void SpotLight::init() {
	setAngle(angle);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
}
