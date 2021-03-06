#pragma once

#include <cmath>
#include <string>
#include <vector>
#include "Point3D.h"
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern const unsigned int maxLevels;

double degToRad(double deg);
bool fileExists(const string& fileName);
Point3D normalizeVector(Point3D normal);
Point3D calculateSurfaceNormal(vector<Point3D> polygonVertexes);
