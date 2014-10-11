#pragma once

#include "CGFscene.h"
#include "Globals.h"
#include "SceneGraph.h"

class GraphScene: public CGFscene {
private:
	Globals* globals;
	SceneGraph* graph;
	CGFlight* light0;
	GLenum drawingMode;

public:
	GraphScene(const char* xmlPath);
	virtual ~GraphScene();

	void init();
	void initLights();
	void update(unsigned long sysTime);
	void display();

	void setDrawingMode(GLenum mode);
};
