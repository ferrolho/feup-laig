#include "Patch.h"
#include <GL/glut.h>

GLfloat texturePoints2[4][2] = { { 0.0, 1.0 }, { 0.0, 0.0 }, { 1.0, 1.0 }, {
		1.0, 0.0 } };

Patch::Patch(int order, int partsU, int partsV, string compute,
		float* controlPoints, Texture* texture) {
	this->order = order + 1;
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
	this->controlPoints = controlPoints;
	this->texture = texture;

	uStride = 3;
	vStride = uStride * (partsV + 1);
}

Patch::~Patch() {
	delete (texture);
}

void Patch::draw() {
	GLint savedFrontFaceMode;
	glGetIntegerv(GL_FRONT_FACE, &savedFrontFaceMode);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_AUTO_NORMAL);
	glFrontFace(GL_CW);

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, uStride, order, 0.0, 1.0, vStride,
			order, controlPoints);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
			&texturePoints2[0][0]);

	glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, partsU, 0, partsV);

	glFrontFace(savedFrontFaceMode);
	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_VERTEX_3);
}

void Patch::updateTexture(Texture* texture) {
	this->texture = texture;
}
