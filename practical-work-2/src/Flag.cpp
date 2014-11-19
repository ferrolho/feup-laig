#include "Flag.h"

Flag::Flag(Texture* texture) {
	// TODO a maria tem de acabar isto!!
	this->texture = NULL;
}

Flag::~Flag() {

}

void Flag::draw() {

}

void Flag::updateTexture(Texture* texture) {
	this->texture = texture;
}

