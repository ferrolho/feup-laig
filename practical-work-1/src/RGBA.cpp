#include "RGBA.h"

#include <sstream>

RGBA::RGBA() {
	r = g = b = 0;
	a = 1;
}

RGBA::RGBA(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

RGBA::~RGBA() {

}

float RGBA::getR() {
	return r;
}

float RGBA::getG() {
	return g;
}

float RGBA::getB() {
	return b;
}

float RGBA::getA() {
	return a;
}

string RGBA::toString() {
	stringstream ss;

	ss << r << " " << g << " " << b << " " << a;

	return ss.str();
}
