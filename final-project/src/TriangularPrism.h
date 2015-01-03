#pragma once

#include "Utilities.h"
#include "Primitive.h"
#include "Triangle.h"
#include "Plane.h"
#include "CGFapplication.h"

class TriangularPrism: public Primitive {
private:
	vector<Point2D*> basePoints;
	vector<Point3D*> drawPoints;
	vector<float> baseSides;
	vector<float> angles;
	vector<Primitive*> sides;
	Primitive* top, *base;
	float height;
	Texture* texture;

public:
	TriangularPrism(vector<Point2D*> points, float height, Texture* texture);
	virtual ~TriangularPrism();

	void draw();
};
