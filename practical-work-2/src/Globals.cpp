#include "Globals.h"

Globals::Globals() {
	drawing = new Drawing();
	culling = new Culling();
	lighting = new Lighting();
}

Globals::Globals(Globals* globals) {
	drawing = globals->drawing;
	culling = globals->culling;
	lighting = globals->lighting;
}

Globals::Globals(Drawing* drawing, Culling* culling, Lighting* lighting) {
	this->drawing = drawing;
	this->culling = culling;
	this->lighting = lighting;
}

Globals::~Globals() {
}

Culling* Globals::getCulling() {
	return culling;
}

Drawing* Globals::getDrawing() {
	return drawing;
}

Lighting* Globals::getLighting() {
	return lighting;
}

void Globals::setCulling(Culling* culling) {
	this->culling = culling;
}

void Globals::setDrawing(Drawing* drawing) {
	this->drawing = drawing;
}

void Globals::setLighting(Lighting* lighting) {
	this->lighting = lighting;
}
