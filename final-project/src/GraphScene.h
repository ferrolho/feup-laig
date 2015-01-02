#pragma once

#include "Cameras.h"
#include "CGFscene.h"
#include "Eximo.h"
#include "Globals.h"
#include "Lights.h"
#include "SceneGraph.h"

#include "GraphSceneUI.h"

class GraphScene: public CGFscene {
	friend GraphSceneUI;

private:
	Globals* globals;
	Cameras* cameras;
	Lights* lights;
	SceneGraph* graph;
	Eximo* eximo;

	Connection* connection;
	Message* message;

	CGFobject* obj;
	CGFappearance* materialAppearance;

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
