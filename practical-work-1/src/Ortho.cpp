#include "Ortho.h"

Ortho::Ortho() {
	this->direction = 'x';
	this->left = 0.0;
	this->right = 0.0;
	this->top = 0.0;
	this->bottom = 0.0;
}

Ortho::Ortho(Ortho* ortho) {
	this->direction = ortho->direction;
	this->left = ortho->left;
	this->right = ortho->right;
	this->top = ortho->top;
	this->bottom = ortho->bottom;
}

Ortho::Ortho(string id, float near, float far, char direction, float left,
		float right, float top, float bottom) :
		Camera(id, near, far) {
	this->direction = direction;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

Ortho::~Ortho() {

}

char Ortho::getDirection() {
	return direction;
}

float Ortho::getLeft() {
	return left;
}

float Ortho::getRight() {
	return right;
}

float Ortho::getTop() {
	return top;
}

float Ortho::getBottom() {
	return bottom;
}
