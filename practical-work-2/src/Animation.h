#pragma once

#include <string>

using namespace std;

class Animation {
private:
	string id;
	float span;

public:
	Animation(string id, float span);
	virtual ~Animation();

	string getId();
};
