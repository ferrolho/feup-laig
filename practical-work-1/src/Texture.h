#pragma once

#include <string>

using namespace std;

class Texture {
private:
	string id, file;
	float texLenght_s, texLenght_t;

public:
	Texture(const string& id, const string& file, float texLenght_s,
			float texLenght_t);
	virtual ~Texture();
};
