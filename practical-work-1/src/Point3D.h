#pragma once

#include <string>
using namespace std;

class Point3D {
private:
	float x, y, z;

public:
	Point3D();
	Point3D(float x, float y, float z);
	virtual ~Point3D();

	float getX();
	float getY();
	float getZ();

	string toString();
};
