#pragma once

#include <string>

#include "CGFtexture.h"

using namespace std;

class Texture : public CGFtexture {
private:
	string id, file;
	float texLenght_s, texLenght_t;

public:
	Texture(const Texture* texture);
	Texture(const string& id, const string& file, float texLenght_s,
			float texLenght_t);
	virtual ~Texture();

	const string getId();
	const string getFilepath();
	const float getTexLenght_s();
	const float getTexLenght_t();
};
