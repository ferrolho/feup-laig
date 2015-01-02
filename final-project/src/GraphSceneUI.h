#pragma once

#include "CGFinterface.h"
#include "Point2D.h"

class GraphSceneUI: public CGFinterface {
public:
	bool srcSelected, destSelected;
	Point2D srcCell, destCell;

private:
	bool initValuesUpdated;
	int drawingModeRadioGroupSelectedItemID;
	int shadingModeRadioGroupSelectedItemID;
	int activeCameraRadioGroupSelectedItemID;

public:
	GraphSceneUI();
	~GraphSceneUI();

	void initGUI();
	void initDrawingModePanel();
	void initShadingModePanel();
	void initCamerasPanel();
	void initLightsPanel();
	void initShadersPanel();
	void initAnimationsPanel();
	void updateInitValues();

	void processGUI(GLUI_Control* ctrl);
	void processKeyboard(unsigned char key, int x, int y);

	virtual void processMouse(int button, int state, int x, int y);
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]);
};
