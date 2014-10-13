#include "Utilities.h"

#include <fstream>

const double pi180 = M_PI / 180;
const unsigned int maxLevels = 20;

double degToRad(double deg) {
	return deg * pi180;
}

bool fileExists(const string &fileName) {
	ifstream infile(fileName.c_str());
	return infile.good();
}

Point3D normalizeVector(Point3D normal) {
	double powX = pow(normal.getX(), 2);
	double powY = pow(normal.getY(), 2);
	double powZ = pow(normal.getZ(), 2);

	double length = sqrt(powX + powY + powZ);

	return normal /= length;
}

// newell's method
Point3D calculateSurfaceNormal(vector<Point3D> polygonVertexes) {
	double x = 0, y = 0, z = 0;

	for (unsigned int i = 0; i < polygonVertexes.size(); i++) {
		Point3D current = polygonVertexes[i];
		Point3D next = polygonVertexes[(i + 1) % polygonVertexes.size()];

		x += (current.getY() - next.getY()) * (current.getZ() + next.getZ());
		y += (current.getZ() - next.getZ()) * (current.getX() + next.getX());
		z += (current.getX() - next.getX()) * (current.getY() + next.getY());
	}

	return normalizeVector(Point3D(x, y, z));
}
