#pragma once

#include "CGFinterface.h"
#include "Point2D.h"
#include "Eximo.h"

class MouseState {
public:
	MouseState(int button, int state, int x, int y);

	void update(int button, int state, int x, int y);

	int button;
	int state;
	int x, y;
};

class GraphSceneUI: public CGFinterface {
public:
	bool selectedAnotherCell;
	Point2D selectedCell;
	MouseState* prevMouseState;

private:
	bool initValuesUpdated;
	int drawingModeRadioGroupSelectedItemID;
	int shadingModeRadioGroupSelectedItemID;
	int activeCameraRadioGroupSelectedItemID;
	int activeThemeRadioGroupSelectedItemID;

public:
	GraphSceneUI();
	~GraphSceneUI();

	void initGUI();
	void initDrawingModePanel();
	void initShadingModePanel();
	void initCamerasPanel();
	void initLightsPanel();
	void initGameControlPanel();
	void initThemesPanel();
	void initClockPanel();
	void updateInitValues();

	void processGUI(GLUI_Control* ctrl);
	void processKeyboard(unsigned char key, int x, int y);

	virtual void processMouse(int button, int state, int x, int y);
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]);
};
