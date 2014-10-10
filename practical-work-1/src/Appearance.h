#pragma once

#include "CGFappearance.h"
#include <string.h>
#include <vector>

#include "RGBA.h"

using namespace std;

struct RGB {
	float rgb[3];
};

class Appearance {
private:
	string id, textureRef;
	float shininess;
	vector<RGBA* > refletionValues;
	CGFappearance* appearance;

public:
	Appearance(string id, float shininess, string textureRef, vector<RGBA* > reflectionValues);
	virtual ~Appearance();
	string getId();
	CGFappearance* buildAppearance(float shininess, string textureRef, vector<RGBA* > reflectionValues);

};



