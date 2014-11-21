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
	void clearBackground();
	void display();

	Globals* getGlobals();
	Cameras* getCameras();
	Lights* getLights();
	void restartAnimations();
	void setActiveCamera(Camera* camera);

	static int WIND, FPS;
};
