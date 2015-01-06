#pragma once

#include "CGFapplication.h"
#include "Point3D.h"
#include <map>
#include <string>

using namespace std;

class Camera: public CGFcamera {
protected:
	string id;
	float near, far;

public:
	Camera(string id, float near, float far);

	string getId();
};

class Perspective: public Camera {
private:
	float angle;

public:
	Perspective(string id, float near, float far, float angle, Point3D* pos,
			Point3D* target);
};

class LockedPerspective: public Camera {
private:
	float angle, lastRotation, rotation;

public:
	bool rotating;
	LockedPerspective(string id, float near, float far, float angle,
			Point3D* pos, Point3D* target);

	void update(unsigned long deltaTime);
	virtual void applyView();
};

class Ortho: public Camera {
private:
	char direction;
	float left, right, top, bottom;

public:
	Ortho(string id, float near, float far, char direction, float left,
			float right, float top, float bottom);

	void applyView();
	void updateProjectionMatrix(int width, int height);
};

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
