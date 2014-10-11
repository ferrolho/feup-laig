#pragma once

#include <string>
using namespace std;

class RGBA {
private:
	float rgba[4];

public:
	RGBA();
	RGBA(float r, float g, float b, float a);
	virtual ~RGBA();

	float* getRGBA();
	float getR();
	float getG();
	float getB();
	float getA();

	string toString();
};
