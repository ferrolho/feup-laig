#include "Cylinder.h"

Cylinder::Cylinder(float base, float top, float height, int slices, int stacks) :
		Primitive(CYLINDER) {
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;


	// --- Starting variables to do top and base --- //
	float anglePerSlice = ((2.0 * PI) / this->slices);
	float currentAngle = 0.0;

	for (unsigned int i = 0; i < slices; i++) {
		topAndBasePoints.push_back(new Point3D(0 * sin(currentAngle),
				top * cos(currentAngle), this->height));
		currentAngle += anglePerSlice;
	}
	printf("Aqui");
}

Cylinder::~Cylinder() {
}

void Cylinder::draw() {
	gluCylinder(gluNewQuadric(), base, top, height, slices, stacks);

	// --- Faces --- //
	// --- Top Face --- //

	/*gluBeginPolygon(new GLUtesselator);
	for (unsigned int i = 0; i < topAndBasePoints.size(); i++) {
		glVertex3f(topAndBasePoints[i]->getX(), topAndBasePoints[i]->getY(),
				topAndBasePoints[i]->getZ());
	}
	gluEndPolygon(new GLUtesselator);*/

}
