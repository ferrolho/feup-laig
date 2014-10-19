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

	virtual void initGUI();
	void initDrawingModePanel();
	void initShadingModePanel();
	void initCamerasPanel();
	void initLightsPanel();
	void updateInitValues();

	void processGUI(GLUI_Control* ctrl);
	virtual void processKeyboard(unsigned char key, int x, int y);
};
