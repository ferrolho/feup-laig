#include "Globals.h"

Globals::Globals() {
	drawing = new Drawing();
}

Globals::Globals(Globals* globals) {
	drawing = globals->drawing;
}

Globals::Globals(Drawing* drawing) {
	this->drawing = drawing;
}

Globals::~Globals() {
}

Drawing* Globals::getDrawing() {
	return drawing;
}

void Globals::setDrawing(Drawing* drawing) {
	this->drawing = drawing;
}
