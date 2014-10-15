#pragma once

#include <string>
#include "RGBA.h"
using namespace std;

class Drawing {
private:
	int mode, shading;
	RGBA* background;

public:
	Drawing();
	Drawing(string mode, string shading, RGBA* background);
	virtual ~Drawing();

	int getMode();
	int getShading();
	RGBA* getBackground();
};
