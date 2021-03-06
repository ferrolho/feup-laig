#pragma once

#include <cmath>
#include <string>
#include <vector>
#include "Point3D.h"
#include "Point2D.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern const unsigned int maxLevels;

bool fileExists(const string& fileName);

double degToRad(double deg);

Point3D normalizeVector(Point3D normal);
Point3D calculateSurfaceNormal(vector<Point3D> polygonVertexes);

float calculateAngleBetween(Point3D u, Point3D v);
float getDistanceBetweenPoints(Point3D p1, Point3D p2);
Point3D* getDirectionBetweenPoints(Point3D p1, Point3D p2, float distance);
