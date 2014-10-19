#include "Lights.h"

Lights::Lights() {
}

Lights::Lights(Lights* lights) {
	this->lights = lights->lights;
}

Lights::~Lights() {
}

void Lights::add(Light* light) {
	if (lights.size() < 8)
		lights.push_back(light);
}

void Lights::init() {
	for (unsigned int i = 0; i < lights.size(); i++)
		lights[i]->init();
}

void Lights::update() {
	for (unsigned int i = 0; i < lights.size(); i++)
		lights[i]->update();
}

void Lights::draw() {
	for (unsigned int i = 0; i < lights.size(); i++)
		lights[i]->draw();
}

vector<Light*>* Lights::getLights() {
	return &lights;
}
