#pragma once

#include <string>
using namespace std;

class Culling {
private:
	int face, order;

public:
	Culling();
	Culling(string face, string order);
	virtual ~Culling();

	int getFace();
	int getOrder();
};
