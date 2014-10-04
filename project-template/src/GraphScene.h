#pragma once

#include "CGFscene.h"

class GraphScene: public CGFscene {
public:
	GraphScene();
	void init();
	void update(unsigned long sysTime);
	void display();
	virtual ~GraphScene();
};
