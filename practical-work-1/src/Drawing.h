#pragma once

#include <string>
#include "CGFapplication.h"
#include "RGBA.h"
using namespace std;

class Drawing {
private:
	GLenum mode, shading;
	RGBA* background;

public:
	Drawing();
	Drawing(string mode, string shading, RGBA* background);
	virtual ~Drawing();

	int getMode();
	int getShading();
	RGBA* getBackground();
	void setMode(GLenum mode);
	void setShading(GLenum shading);
};
