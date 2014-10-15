#include "Lighting.h"

Lighting::Lighting() {
	doublesided = true;
	local = false;
	enabled = true;
	ambient = new RGBA(1, 1, 1, 1);
}

Lighting::Lighting(string doublesided, string local, string enabled,
		RGBA* ambient) {
	if (doublesided.compare("true") == 0)
		this->doublesided = true;
	else if (doublesided.compare("false") == 0)
		this->doublesided = false;

	if (local.compare("true") == 0)
		this->local = true;
	else if (local.compare("false") == 0)
		this->local = false;

	if (enabled.compare("true") == 0)
		this->enabled = true;
	else if (enabled.compare("false") == 0)
		this->enabled = false;

	this->ambient = ambient;
}

Lighting::~Lighting() {
}

RGBA* Lighting::getAmbient() {
	return ambient;
}

bool Lighting::getDoubleSided() {
	return doublesided;
}

bool Lighting::getEnabled() {
	return enabled;
}

bool Lighting::getLocal() {
	return local;
}

void Lighting::setAmbient(RGBA* ambient) {
	this->ambient = ambient;
}

void Lighting::setDoubleSided(bool doublesided) {
	this->doublesided = doublesided;
}

void Lighting::setEnabled(bool enabled) {
	this->enabled = enabled;
}

void Lighting::setLocal(bool local) {
	this->local = local;
}
