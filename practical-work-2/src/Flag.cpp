#include "Flag.h"

#include <glew.h>
#include "GraphScene.h"

Flag::Flag(string texture) :
		Plane(50) {
	this->texture = new CGFtexture(texture);

	startTime = 0;
	deltaTime = 0;
	wind = GraphScene::WIND;

	deltaTimeLoc = 0;
	textureLoc = 0;
	windLoc = 0;

	shader.init("res/flag.vert", "res/flag.frag");
}

Flag::~Flag() {
}

void Flag::update(unsigned long t) {
	if (GraphScene::WIND != wind)
		wind = GraphScene::WIND;

	setTime(t * 0.001);
}

void Flag::draw() {
	shader.bind();

	deltaTimeLoc = glGetUniformLocation(shader.id(), "deltaTime");
	glUniform1f(deltaTimeLoc, deltaTime);

	windLoc = glGetUniformLocation(shader.id(), "wind");
	glUniform1f(windLoc, wind);

	textureLoc = glGetUniformLocation(shader.id(), "texture");
	glUniform1i(textureLoc, 0);

	glActiveTexture(GL_TEXTURE0);
	texture->apply();

	glPushMatrix();
	glScaled(10, 1, 10);

	Plane::draw();

	glPopMatrix();

	shader.unbind();
}

void Flag::setTime(float time) {
	startTime == 0 ? startTime = time : deltaTime = time - startTime;
}
