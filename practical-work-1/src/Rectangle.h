#pragma once

#include <math.h>

#include "Point3D.h"
#include "Primitive.h"
#include "Texture.h"

class Rectangle: public Primitive {
private:
	Point3D p1, p2;
	float s , t;
	Texture* texture;

public:
	Rectangle(Point3D p1, Point3D p2, Texture* texture);
	virtual ~Rectangle();

	void draw();
	float getHeight();
	float getWidth();
};
