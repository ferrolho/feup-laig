#pragma once

#include <string>
#include "RGBA.h"
using namespace std;

class Lighting {
private:
	bool doublesided, local, enabled;
	RGBA* ambient;

public:
	Lighting();
	Lighting(string doublesided, string local, string enabled, RGBA* ambient);
	virtual ~Lighting();

	RGBA* getAmbient();
	bool getDoubleSided();
	bool getEnabled();
	bool getLocal();
	void setAmbient(RGBA* ambient);
	void setDoubleSided(bool doublesided);
	void setEnabled(bool enabled);
	void setLocal(bool local);
};
