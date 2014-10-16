#pragma once

#include <string>
using namespace std;

class Point3D {
private:
	float x, y, z;
	float xyz[4];

public:
	Point3D();
	Point3D(float x, float y, float z);
	virtual ~Point3D();

	float getX();
	float getY();
	float getZ();
	float* getXYZ();

	string toString();

	Point3D& operator=(const Point3D &point) {
		if (this == &point)
			return *this;

		x = point.x;
		y = point.y;
		z = point.z;

		return *this;
	}

	friend Point3D operator+(Point3D start, Point3D vec) {
		double x, y, z;

		x = start.x + vec.x;
		y = start.y + vec.y;
		z = start.z + vec.z;

		return Point3D(x, y, z);
	}

	friend Point3D operator-(Point3D end, Point3D start) {
		double x, y, z;

		x = end.x - start.x;
		y = end.y - start.y;
		z = end.z - start.z;

		return Point3D(x, y, z);
	}

	friend Point3D operator*(double n, Point3D vec) {
		double x, y, z;

		x = n * vec.x;
		y = n * vec.y;
		z = n * vec.z;

		return Point3D(x, y, z);
	}

	friend Point3D operator/(Point3D vec, double n) {
		double x, y, z;

		x = vec.x / n;
		y = vec.y / n;
		z = vec.z / n;

		return Point3D(x, y, z);
	}

	Point3D& operator/=(double n) {
		this->x /= n;
		this->y /= n;
		this->z /= n;

		return *this;
	}
};
