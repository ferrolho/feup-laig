#include "Utilities.h"

#include <fstream>

const unsigned int maxLevels = 20;

const double pi180 = M_PI / 180;

double degToRad(double deg) {
	return deg * pi180;
}

double radToDeg(double rad) {
	return rad * pi180;
}

bool fileExists(const string &fileName) {
	ifstream infile(fileName.c_str());
	return infile.good();
}

Point3D normalizeVector(Point3D normal) {
	float powX = pow(normal.getX(), 2);
	float powY = pow(normal.getY(), 2);
	float powZ = pow(normal.getZ(), 2);

	float length = sqrt(powX + powY + powZ);

	return normal /= length;
}

// newell's method
Point3D calculateSurfaceNormal(vector<Point3D> polygonVertexes) {
	float x = 0, y = 0, z = 0;

	for (unsigned int i = 0; i < polygonVertexes.size(); i++) {
		Point3D current = polygonVertexes[i];
		Point3D next = polygonVertexes[(i + 1) % polygonVertexes.size()];

		x += (current.getY() - next.getY()) * (current.getZ() + next.getZ());
		y += (current.getZ() - next.getZ()) * (current.getX() + next.getX());
		z += (current.getX() - next.getX()) * (current.getY() + next.getY());
	}

	return normalizeVector(Point3D(x, y, z));
}

float calculateAngleBetweenPoints(Point3D u, Point3D v) {
	float num = u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();

	float uX2 = u.getX() * u.getX();
	float uY2 = u.getY() * u.getY();
	float uZ2 = u.getZ() * u.getZ();
	float vX2 = v.getX() * v.getX();
	float vY2 = v.getY() * v.getY();
	float vZ2 = v.getZ() * v.getZ();

	float denom = sqrt(uX2 + uY2 + uZ2) * sqrt(vX2 + vY2 + vZ2);

	return (radToDeg(acos(num / denom)) /* 1000*/);
}

// distance between two points
float getDistanceBetweenPoints(Point3D p1, Point3D p2) {
	return (sqrt(
			pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2)
					+ pow(p2.getZ() - p1.getZ(), 2)));
}

Point3D* getDirectionBetweenPoints(Point3D p1, Point3D p2, float distance) {
	Point3D direction = p2 - p1;

	// normalizing point
	direction /= distance;

	return new Point3D(direction);
}
