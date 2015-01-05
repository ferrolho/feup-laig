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
	Camera(string id, float near, float far) :
			CGFcamera() {
		this->id = id;
		this->near = near;
		this->far = far;
	}

	string getId() {
		return id;
	}
};

class Perspective: public Camera {
private:
	float angle;

public:
	Perspective(string id, float near, float far, float angle, Point3D* pos,
			Point3D* target) :
			Camera(id, near, far) {
		position[0] = pos->getX();
		position[1] = pos->getY();
		position[2] = pos->getZ();

		this->angle = angle;

		this->target[0] = target->getX();
		this->target[1] = target->getY();
		this->target[2] = target->getZ();

		rotation[0] = 45;
		rotation[1] = 180;
	}

	virtual void applyView() {
		CGFcamera::applyView();
	}
};

class LockedPerspective: public Camera {
private:
	float angle, lastRotation, rotation;

public:
	bool rotating;
	LockedPerspective(string id, float near, float far, float angle,
			Point3D* pos, Point3D* target) :
			Camera(id, near, far) {
		position[0] = pos->getX();
		position[1] = pos->getY();
		position[2] = pos->getZ();

		this->angle = angle;

		this->target[0] = target->getX();
		this->target[1] = target->getY();
		this->target[2] = target->getZ();

		rotating = false;
		lastRotation = rotation = 180;
	}

	void update(unsigned long deltaTime) {
		if (rotating) {
			rotation += 0.1 * deltaTime;

			if (rotation - lastRotation >= 180) {
				rotating = false;

				if (lastRotation == 180)
					rotation = 0;
				else
					rotation = 180;

				lastRotation = rotation;
			}
		}
	}

	virtual void applyView() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(position[0], position[1], position[2], target[0], target[1],
				target[2], 0, 1, 0);

		glRotatef(rotation, 0.f, 1.f, 0.f);
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
