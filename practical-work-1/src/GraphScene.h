#pragma once

#include "CGFscene.h"
#include "Globals.h"
#include "Cameras.h"
#include "Lights.h"
#include "SceneGraph.h"

class GraphScene: public CGFscene {
private:
	Globals* globals;
	Cameras* cameras;
	Lights* lights;
	SceneGraph* graph;

public:
	GraphScene(const char* xmlPath);
	virtual ~GraphScene();

	void init();
	void update(unsigned long sysTime);
	void display();

	Globals* getGlobals();
	Lights* getLights();
};
