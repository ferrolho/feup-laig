#pragma once

#include <string>
#include "RGBA.h"
using namespace std;

class Drawing {
private:
	string mode, shading;
	RGBA* background;

public:
	Drawing();
	Drawing(string mode, string shading, RGBA* background);
	virtual ~Drawing();

	string getMode();
	string getShading();
	RGBA* getBackground();
};
