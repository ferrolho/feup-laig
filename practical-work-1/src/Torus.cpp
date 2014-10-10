#include "Torus.h"
#include "Utilities.h"
#include <iostream>

#include "GL/glut.h"

Torus::Torus(float inner, float outer, int slices, int loops) :
		Primitive(TORUS) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;

	// variables to build torus
	float loopsDelta = (2.0 * M_PI) / loops;
	float slicesDelta = (2.0 * M_PI) / slices;

	float anglePerSlice;
	float dOuter, cosdOuter, sindOuter;
	float dInner = 0.0, cosdInner = 1.0, sindInner = 0.0;
	int count = 0;

	// outer loop
	for (unsigned int i = 0; i < loops; i++) {
		dOuter = dInner + loopsDelta;
		cosdOuter = cos(dOuter);
		sindOuter = sin(dOuter);

		anglePerSlice = 0.0;

		// inner loop
		for (unsigned int j = 0; j < slices + 1; j++) {
			float cosAnglePerSlice, sinAnglePerSlice, dist;

			anglePerSlice += slicesDelta;
			cosAnglePerSlice = cos(anglePerSlice);
			sinAnglePerSlice = sin(anglePerSlice);
			dist = outer + (inner * cosAnglePerSlice);


			torusPoints.push_back(new Point3D(cosdOuter * dist, -sindOuter * dist,
					inner * sinAnglePerSlice));

			torusPoints.push_back(new Point3D(cosdInner * dist, -sindInner * dist,
					inner * sinAnglePerSlice));
			count++;
		}

		dInner = dOuter;
		cosdInner = cosdOuter;
		sindInner = sindOuter;
	}
}

Torus::~Torus() {
}

void Torus::draw() {
	// drawing torus
	int vecPos = 0;
	for (unsigned int i = 0; i < loops; i++) {
		glBegin(GL_QUAD_STRIP);
		for (unsigned int j = 0; j < slices + 1; j++) {
			glVertex3f(torusPoints[vecPos]->getX(), torusPoints[vecPos]->getY(),
					torusPoints[vecPos]->getZ());
			glVertex3f(torusPoints[vecPos+1]->getX(), torusPoints[vecPos+1]->getY(),
								torusPoints[vecPos+1]->getZ());
			vecPos += 2;
		}
		glEnd();
	}
}

