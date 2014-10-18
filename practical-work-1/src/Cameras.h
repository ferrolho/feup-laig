#pragma once

#include <vector>
#include "Camera.h"
using namespace std;

class Cameras {
private:
	vector<Camera*> cameras;

public:
	Cameras();
	Cameras(Cameras* camera);
	virtual ~Cameras();

	void init();
	void update();
	void draw();

	void add(Camera* camera);
};
