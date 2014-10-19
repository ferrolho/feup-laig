#pragma once

#include <map>
#include "Camera.h"

class Cameras {
private:
	map<string, Camera*> cameras;
	string activeCamera;

public:
	Cameras();
	Cameras(Cameras* camera);
	virtual ~Cameras();

	void add(Camera* camera);
	string getActiveCameraID();
	Camera* getActiveCamera();
	map<string, Camera*>* getCameras();
	void setActiveCameraID(string camera);
};
