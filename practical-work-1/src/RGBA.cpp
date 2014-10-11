#include "RGBA.h"

#include <sstream>

RGBA::RGBA() {
	rgba[0] = 0;
	rgba[1] = 0;
	rgba[2] = 0;
	rgba[3] = 1;
}

RGBA::RGBA(float r, float g, float b, float a) {
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}

RGBA::~RGBA() {

}

float* RGBA::getRGBA() {
	return rgba;
}

float RGBA::getR() {
	return rgba[0];
}

float RGBA::getG() {
	return rgba[1];
}

float RGBA::getB() {
	return rgba[2];
}

float RGBA::getA() {
	return rgba[3];
}

string RGBA::toString() {
	stringstream ss;

	ss << rgba[0] << " " << rgba[1] << " " << rgba[2] << " " << rgba[3];

	return ss.str();
}
