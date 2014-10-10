#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
using namespace std;

extern const int maxLevels;

#define FOR(i, a, b) for(unsigned int i = a; i < b; i++)
#define foreach(v, it) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)

double degToRad(double deg);
bool fileExists(const string& fileName);
