#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#define foreach(v, it) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)

double degToRad(double deg);
