#include "Drawing.h"

Drawing::Drawing() {
	mode = "fill";
	shading = "flat";
	background = new RGBA();
}

Drawing::Drawing(string mode, string shading, RGBA* background) {
	this->mode = mode;
	this->shading = shading;
	this->background = background;
}

Drawing::~Drawing() {
}

string Drawing::getMode() {
	return mode;
}

string Drawing::getShading() {
	return shading;
}

RGBA* Drawing::getBackground() {
	return background;
}
