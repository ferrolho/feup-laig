#include "SpotLight.h"

#include "CGFapplication.h"

SpotLight::SpotLight(string strId, bool enabled, bool marker, Point3D pos, Point3D target,
		float angle, float exponent, Components* components) :
		Light(strId, enabled, marker, pos, target, components) {
	this->angle = angle;
	this->exponent = exponent;
}

SpotLight::SpotLight(string strId, string enabled, string marker, Point3D pos, Point3D target,
		float angle, float exponent, Components* components) :
		Light(strId, enabled, marker, pos, target, components) {
	this->angle = angle;
	this->exponent = exponent;
}

SpotLight::~SpotLight() {
}

void SpotLight::init() {
	setAngle(angle);
	glLightf(id, GL_SPOT_EXPONENT, exponent);
}
