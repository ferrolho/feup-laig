#pragma once

#include "Animation.h"
#include "Cameras.h"
#include "CGFscene.h"
#include "Eximo.h"
#include "Globals.h"
#include "GraphSceneUI.h"
#include "Lights.h"
#include "SceneGraph.h"
#include "ClockGame.h"

enum TurnType {
	FREE_TURN,
	MANDATORY_JUMP,
	MANDATORY_CAPTURE,
	PLACE_2_CHECKERS,
	PLACE_1_CHECKER
};

enum TurnState {
	CHECK_IF_GAME_IS_OVER, SELECTING_SRC, SELECTING_DEST, GAME_OVER
};

class GraphScene: public CGFscene {
	friend GraphSceneUI;

private:
	Globals* globals;
	Cameras* cameras;
	Lights* lights;
	SceneGraph* graph;
	Eximo* eximo;
	ClockGame* gameChronometer;
	map<string, Appearance*> appearances;

	Connection* connection;
	Message* message;

	LockedPerspective* playerCam;

public:
	TurnState turnState;
	TurnType turnType;

	CGFobject* obj;
	CGFappearance* materialAppearance;

public:
	GraphScene(const char* xmlPath);
	virtual ~GraphScene();

	void init();
	void update(unsigned long sysTime);
	void clearBackground();
	void display();
	void displayRenderMode();
	void displaySelectMode();

	Globals* getGlobals();
	Cameras* getCameras();
	Lights* getLights();
	SceneGraph* getGraph();
	ClockGame* getClockGame();
	void restartAnimations();
	void undoMove();
	void setActiveCamera(Camera* camera);

	void reviewGame();

	// special class variables
	static int WIND, FPS;
};
