#include "Plane.h"
#include <GL/glut.h>

GLfloat ctrlpoints[4][3] = { { -0.5, 0.0, 0.5 }, { -0.5, 0.0, -0.5 }, { 0.5,
		0.0, 0.5 }, { 0.5, 0.0, -0.5 } };

GLfloat nrmlcompon[4][3] = { { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 1.0,
		0.0 }, { 0.0, 1.0, 0.0 } };

GLfloat textpoints[4][2] = { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 0.0 }, { 1.0,
		1.0 } };

Plane::Plane(unsigned int divisions) {
	this->divisions = divisions;
	this->myTexture = new CGFtexture("res/ground.jpg");
}

Plane::~Plane() {
	delete (myTexture);
}

void Plane::draw() {
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glColor3f(1.0, 1.0, 1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2,
			&ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
			&textpoints[0][0]);

	glMapGrid2f(divisions, 0.0, 1.0, divisions, 0.0, 1.0);

	myTexture->apply();

	glEvalMesh2(GL_FILL, 0, divisions, 0, divisions);

	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_VERTEX_3);
}
