#pragma once

#include <string>
#include "CGFshader.h"
#include "Plane.h"
#include "Texture.h"

class Flag: public Plane {
public:
	Flag(string texture);
	~Flag();

	void update(unsigned long t);
	void draw();

	void setTime(float time);
	void setWind(int wind);

private:
	CGFshader shader;
	CGFtexture* texture;

	int deltaTimeLoc;
	int textureLoc;
	int windLoc;

	unsigned long startTime;
	float deltaTime;
	int wind;
};
