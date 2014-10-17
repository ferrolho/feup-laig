#include "Drawing.h"

#include "CGFapplication.h"

Drawing::Drawing() {
	mode = GL_FILL;
	shading = GL_FLAT;
	background = new RGBA();
}

Drawing::Drawing(string mode, string shading, RGBA* background) {
	if (mode.compare("point") == 0)
		this->mode = GL_POINT;
	else if (mode.compare("line") == 0)
		this->mode = GL_LINE;
	else if (mode.compare("fill") == 0)
		this->mode = GL_FILL;

	if (shading.compare("flat") == 0)
		this->shading = GL_FLAT;
	else if (shading.compare("gouraud") == 0)
		this->shading = GL_SMOOTH;

	this->background = background;
}

Drawing::~Drawing() {
}

int Drawing::getMode() {
	return mode;
}

int Drawing::getShading() {
	return shading;
}

RGBA* Drawing::getBackground() {
	return background;
}
