#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>
#include "Point3D.h"
using namespace std;

extern const unsigned int maxLevels;

#define FOR(i, a, b) for(unsigned int i = a; i < b; i++)
#define foreach(v, it) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)

double degToRad(double deg);
bool fileExists(const string& fileName);
Point3D normalizeVector(Point3D normal);
Point3D calculateSurfaceNormal(vector<Point3D> polygonVertexes);
