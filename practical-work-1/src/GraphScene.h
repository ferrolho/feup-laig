#pragma once

#include "CGFscene.h"
#include "Globals.h"
#include "Lights.h"
#include "SceneGraph.h"

class GraphScene: public CGFscene {
private:
	Globals* globals;
	Lights* lights;
	SceneGraph* graph;

public:
	GraphScene(const char* xmlPath);
	virtual ~GraphScene();

	void init();
	void update(unsigned long sysTime);
	void display();
};
