#include "Plane.h"
#include <GL/glut.h>

GLfloat controlPoints[4][3] = { { -0.5, 0.0, 0.5 }, { -0.5, 0.0, -0.5 }, { 0.5,
		0.0, 0.5 }, { 0.5, 0.0, -0.5 } };

GLfloat normalComponents[4][3] = { { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0,
		1.0, 0.0 }, { 0.0, 1.0, 0.0 } };

GLfloat texturePoints[4][2] = { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 0.0 }, { 1.0,
		1.0 } };

Plane::Plane(unsigned int divisions, Texture* texture) {
	this->parts = divisions;
	this->texture = texture;
}

Plane::~Plane() {
	delete (texture);
}

void Plane::draw() {
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2,
			&controlPoints[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2,
			&normalComponents[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
			&texturePoints[0][0]);

	glMapGrid2f(parts, 0.0, 1.0, parts, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, parts, 0, parts);

	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_VERTEX_3);
}

void Plane::updateTexture(Texture* texture) {
	this->texture = texture;
}
