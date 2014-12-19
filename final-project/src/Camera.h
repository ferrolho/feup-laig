#pragma once

#include <string>
#include "CGFapplication.h"
#include "Point3D.h"

using namespace std;

class Camera: public CGFcamera {
protected:
	string id;
	float near, far;

public:
	Camera(string id, float near, float far) {
		this->id = id;
		this->near = near;
		this->far = far;
	}

	virtual ~Camera() {
	}

	virtual void applyView() = 0;

	virtual void updateProjectionMatrix(int width, int height) = 0;

	string getId() {
		return id;
	}
};

class Perspective: public Camera {
private:
	float angle;
	Point3D* target;

public:
	Perspective(string id, float near, float far, float angle, Point3D* pos,
			Point3D* target) :
			Camera(id, near, far) {
		position[0] = pos->getX();
		position[1] = pos->getY();
		position[2] = pos->getZ();

		this->angle = angle;
		this->target = target;
	}

	virtual ~Perspective() {
	}

	void applyView() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		int posX = position[0];
		int posY = position[1];
		int posZ = position[2];

		if (posX - target->getX() == 0 && posZ - target->getZ() == 0)
			gluLookAt(posX, posY, posZ, target->getX(), target->getY(),
					target->getZ(), 0, 0, -1);
		else
			gluLookAt(posX, posY, posZ, target->getX(), target->getY(),
					target->getZ(), 0, 1, 0);
	}

	void updateProjectionMatrix(int width, int height) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angle, (float) width / (float) height, near, far);
	}
};

class Ortho: public Camera {
private:
	char direction;
	float left, right, top, bottom;

public:
	Ortho(string id, float near, float far, char direction, float left,
			float right, float top, float bottom) :
			Camera(id, near, far) {
		this->direction = direction;
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}

	virtual ~Ortho() {
	}

	void applyView() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		switch (direction) {
		case 'x':
		case 'X':
			gluLookAt(0, 0, 0, -1, 0, 0, 0, 1, 0);
			break;
		case 'y':
		case 'Y':
			gluLookAt(0, 0, 0, 0, -1, 0, 0, 0, -1);
			break;
		case 'z':
		case 'Z':
			gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
			break;
		}
	}

	void updateProjectionMatrix(int width, int height) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float aspect = (float) width / (float) height;
		glOrtho(left * aspect, right * aspect, bottom, top, near, far);
	}
};
