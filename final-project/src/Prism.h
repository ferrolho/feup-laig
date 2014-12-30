#pragma once

#include "Utilities.h"
#include "Primitive.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "CGFapplication.h"

class Prism: public Primitive {
private:
	vector<Point2D*> basePoints;
	vector<Point3D*> drawPoints;
	vector<float> baseSides;
	vector<Primitive*> sides;
	vector<float> angles;
	float height;
	Primitive* top, *base;

public:
	Prism(vector<Point2D*> points, float height);
	virtual ~Prism();

	void draw();
};
