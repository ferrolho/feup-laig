#include "Torus.h"
#include "Utilities.h"

#include "GL/glut.h"

Torus::Torus(float inner, float outer, int slices, int loops) :
		Primitive(TORUS) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;

	// variables to build torus
	float slicesDelta = (2.0 * M_PI) / slices;
	float loopsDelta = (2.0 * M_PI) / loops;

	float anglePerSlice;
	float dOuter, cosdOuter, sindOuter;
	float dInner = 0.0, cosdInner = 1.0, sindInner = 0.0;

	// outer loop
	for (unsigned int i = 0; i < slices; i++) {
		dOuter = dInner + slicesDelta;
		cosdOuter = cos(dOuter);
		sindOuter = sin(dOuter);

		anglePerSlice = 0.0;

		// inner loop
		for (unsigned int j = 0; j < loops + 1; j++) {
			float cosAnglePerSlice, sinAnglePerSlice, dist;

			anglePerSlice += loopsDelta;
			cosAnglePerSlice = cos(anglePerSlice);
			sinAnglePerSlice = sin(anglePerSlice);
			dist = outer + (inner * cosAnglePerSlice);

			normalPoints.push_back(
					new Point3D(cosdOuter * cosAnglePerSlice,
							-sindOuter * cosAnglePerSlice, sinAnglePerSlice));
			torusPoints.push_back(
					new Point3D(cosdOuter * dist, -sindOuter * dist,
							inner * sinAnglePerSlice));

			normalPoints.push_back(
					new Point3D(cosdInner * cosAnglePerSlice,
							-sindInner * cosAnglePerSlice, sinAnglePerSlice));
			torusPoints.push_back(
					new Point3D(cosdInner * dist, -sindInner * dist,
							inner * sinAnglePerSlice));
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
	for (unsigned int i = 0; i < slices; i++) {
		glBegin(GL_QUAD_STRIP);
		for (unsigned int j = 0; j < loops + 1; j++) {
			glNormal3f(normalPoints[vecPos]->getX(),
					normalPoints[vecPos]->getY(), normalPoints[vecPos]->getZ());
			glVertex3f(torusPoints[vecPos]->getX(), torusPoints[vecPos]->getY(),
					torusPoints[vecPos]->getZ());
			glNormal3f(normalPoints[vecPos + 1]->getX(),
					normalPoints[vecPos + 1]->getY(),
					normalPoints[vecPos + 1]->getZ());
			glVertex3f(torusPoints[vecPos + 1]->getX(),
					torusPoints[vecPos + 1]->getY(),
					torusPoints[vecPos + 1]->getZ());
			vecPos += 2;
		}
		glEnd();
	}
}

