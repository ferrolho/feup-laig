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
	CGFappearance* appearance;
	vector<RGBA*> components;

public:
	Appearance(const string& id, float shininess, const string& textureRef,
			const vector<RGBA*>& components);
	virtual ~Appearance();
	string getId();
	CGFappearance* buildAppearance(float shininess, string textureRef,
			const vector<RGBA*>& reflectionValues);

};

