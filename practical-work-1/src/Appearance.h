#pragma once

#include <string.h>
#include <vector>

#include "RGBA.h"

using namespace std;

class Appearance {
private:
	string id, textureRef;
	float shininess;
	vector<RGBA*> components;

public:
	Appearance(const string& id, float shininess, const string& textureRef,
			const vector<RGBA*>& components);
	virtual ~Appearance();
};

