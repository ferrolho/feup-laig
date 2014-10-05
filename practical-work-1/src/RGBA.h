#pragma once

#include <string>
using namespace std;

class RGBA {
private:
	float r, g, b, a;

public:
	RGBA();
	RGBA(float r, float g, float b, float a);
	virtual ~RGBA();

	float getR();
	float getG();
	float getB();
	float getA();

	string toString();
};
