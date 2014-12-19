#pragma once

#include "CGFinterface.h"

class GraphSceneUI: public CGFinterface {
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
};
