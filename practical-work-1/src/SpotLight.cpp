#include "SpotLight.h"

SpotLight::SpotLight(bool enabled, bool marker, Point3D pos, Point3D target,
		float angle, float exponent, Components* components) :
		Light(enabled, marker, pos, components) {
	this->target = target;
	this->angle = angle;
	this->exponent = exponent;
}

SpotLight::SpotLight(string enabled, string marker, Point3D pos, Point3D target,
		float angle, float exponent, Components* components) :
		Light(enabled, marker, pos, components) {
	this->target = target;
	this->angle = angle;
	this->exponent = exponent;
}

SpotLight::~SpotLight() {
}
