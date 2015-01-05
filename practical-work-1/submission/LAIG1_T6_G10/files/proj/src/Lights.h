#pragma once

#include <vector>
#include "Light.h"
using namespace std;

class Lights {
private:
	vector<Light*> lights;

public:
	Lights();
	Lights(Lights* lights);
	virtual ~Lights();

	void add(Light* light);
	void init();
	void update();
	void draw();

	vector<Light*>* getLights();
};
