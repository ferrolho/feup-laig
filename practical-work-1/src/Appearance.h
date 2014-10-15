#pragma once

#include <string.h>
#include <vector>
#include "CGFappearance.h"
#include "GL/gl.h"
#include "RGBA.h"
#include "Texture.h"
#include "Components.h"
using namespace std;

class Appearance: public CGFappearance {
private:
	string id;
	Texture* texture;

public:
	Appearance(const string& id, float shininess, Texture* texture,
			Components* components);
	virtual ~Appearance();

	string getId();
	Texture* getTexture();
};
