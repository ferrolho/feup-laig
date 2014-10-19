#pragma once

#include <map>
#include "Camera.h"

class Cameras {
private:
	map<string, Camera*> cameras;
	string activedCamera;

public:
	Cameras();
	Cameras(Cameras* camera);
	virtual ~Cameras();

	void add(Camera* camera);
	map<string, Camera*>* getCameras();
	string getActivedCamera();
	void setActivedCamera(string newCamera);
};
