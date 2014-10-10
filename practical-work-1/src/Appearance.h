#pragma once

#include <string.h>

#include "RGBA.h"

using namespace std;

class Appearance {
private:
	string id, textureRef;
	float shininess;
	RGBA* refletionValues;

public:
	Appearance(string id, float shininess, vector<RGBA* > reflectionValues);
	virtual ~Appearance();
};



