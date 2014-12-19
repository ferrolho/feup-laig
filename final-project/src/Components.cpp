#include "Components.h"

Components::Components() {
	this->ambient = new RGBA();
	this->diffuse = new RGBA(1, 1, 1, 1);
	this->specular = new RGBA();
}

Components::Components(RGBA* ambient, RGBA* diffuse, RGBA* specular) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

Components::~Components() {

}

float* Components::getAmbient() {
	return ambient->getRGBA();
}

float* Components::getDiffuse() {
	return diffuse->getRGBA();
}

float* Components::getSpecular() {
	return specular->getRGBA();
}
