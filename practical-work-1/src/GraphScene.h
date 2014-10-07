#pragma once

#include "CGFscene.h"

class GraphScene: public CGFscene {
private:


public:
	GraphScene(char* xmlPath);
	void init();
	void update(unsigned long sysTime);
	void display();
	virtual ~GraphScene();
};
