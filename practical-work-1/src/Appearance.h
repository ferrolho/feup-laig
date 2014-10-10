#pragma once

#include <string.h>
#include <vector>

#include "RGBA.h"

using namespace std;

class Appearance {
private:
	string id, textureRef;
	float shininess;
	vector<RGBA* > refletionValues;

public:
	Appearance(string id, float shininess, string textureRef, vector<RGBA* > reflectionValues);
	virtual ~Appearance();
};



