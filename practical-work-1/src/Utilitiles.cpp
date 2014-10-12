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
