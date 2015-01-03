#include "ExampleObject.h"

float size = 2;

void ExampleObject::draw() {
	glBegin(GL_QUADS);

	glTexCoord2d(0, 0);
	glVertex3d(0, -size, 0);

	glTexCoord2d(1, 0);
	glVertex3d(size, -size, 0);

	glTexCoord2d(1, 1);
	glVertex3d(size, 0, 0);

	glTexCoord2d(0, 1);
	glVertex3d(0, 0, 0);

	glEnd();
}
