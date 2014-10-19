#include "Ortho.h"

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

void Ortho::applyView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 0, 1, 0);
}

void Ortho::updateProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, near, far);
}

/*
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
 */
