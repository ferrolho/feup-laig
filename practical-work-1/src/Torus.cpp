#include "Torus.h"
#include "Utilities.h"

#include "glut.h"

Torus::Torus(float inner, float outer, unsigned int slices, unsigned int loops) :
		Primitive(TORUS) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;

	// variables to build torus
	float theta, phi, theta1;
	float cosTheta, sinTheta;
	float cosTheta1, sinTheta1;
	float ringsDelta, sideDelta;

	ringsDelta = 2.0 * M_PI / (float) loops;
	sideDelta = 2.0 * M_PI / (float) slices;

	theta = 0.0;
	cosTheta = 1.0;
	sinTheta = 0.0;

	float deltaU = 1.0 / (float) slices, deltaV = 1.0 / (float) loops, u = 0,
			v = 0;

	// starting loops
	for (unsigned int i = 0; i < loops; i++) {
		theta1 = theta + ringsDelta;
		cosTheta1 = cos(theta1);
		sinTheta1 = sin(theta1);

		phi = 0.0;

		u = 0;
		for (unsigned int j = 0; j < slices + 1; j++) {
			float cosPhi, sinPhi, dist;

			phi += sideDelta;
			cosPhi = cos(phi);
			sinPhi = sin(phi);
			dist = outer + inner * cosPhi;

			texturePoints.push_back(new Point2D(u, v));
			normalPoints.push_back(
					new Point3D(cosTheta1 * cosPhi, -sinTheta1 * cosPhi,
							sinPhi));
			torusPoints.push_back(
					new Point3D(cosTheta1 * dist, -sinTheta1 * dist,
							inner * sinPhi));

			texturePoints.push_back(new Point2D(u, v + deltaV));
			normalPoints.push_back(
					new Point3D(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi));
			torusPoints.push_back(
					new Point3D(cosTheta * dist, -sinTheta * dist,
							inner * sinPhi));

			if (u >= 1) {
				u = 0;
			} else
				u += deltaU;
		}
		glEnd();

		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;

		v += deltaV;
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
			glTexCoord2f(texturePoints[vecPos]->getX(),
					texturePoints[vecPos]->getY());

			glNormal3f(normalPoints[vecPos]->getX(),
					normalPoints[vecPos]->getY(), normalPoints[vecPos]->getZ());
			glVertex3f(torusPoints[vecPos]->getX(), torusPoints[vecPos]->getY(),
					torusPoints[vecPos]->getZ());

			glTexCoord2f(texturePoints[vecPos + 1]->getX(),
					texturePoints[vecPos + 1]->getY());
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
