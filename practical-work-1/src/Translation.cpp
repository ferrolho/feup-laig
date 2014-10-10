#include "Translation.h"

#include "GL/glu.h"

Translation::Translation(Point3D to) :
		Transform(TRANSLATION) {
	this->to = to;
}

Translation::~Translation() {
}

void Translation::apply() {
	glTranslatef(to.getX(), to.getY(), to.getZ());
}
