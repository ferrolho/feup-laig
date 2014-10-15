#include "Culling.h"

#include "gl.h"

Culling::Culling() {
	face = GL_BACK;
	order = GL_CCW;
}

Culling::Culling(string face, string order) {
	if (face.compare("none") == 0)
		this->face = GL_NONE;
	else if (face.compare("back") == 0)
		this->face = GL_BACK;
	else if (face.compare("front") == 0)
		this->face = GL_FRONT;
	else if (face.compare("both") == 0)
		this->face = GL_FRONT_AND_BACK;

	if (order.compare("ccw") == 0)
		this->order = GL_CCW;
	else if (order.compare("cw") == 0)
		this->order = GL_CW;
}

Culling::~Culling() {
}

int Culling::getFace() {
	return face;
}

int Culling::getOrder() {
	return order;
}
