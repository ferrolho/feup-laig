#pragma once

#include "CGFscene.h"
#include "SceneGraph.h"

class GraphScene: public CGFscene {
private:
	SceneGraph* graph;
	CGFlight* light0;

public:
	GraphScene(const char* xmlPath);
	void init();
	void initLights();
	void update(unsigned long sysTime);
	void display();
	virtual ~GraphScene();
};
