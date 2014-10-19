#pragma once

#include "CGFinterface.h"

class GraphSceneUI: public CGFinterface {
private:
	int drawingModeRadioGroupSelectedItemID;
	int activeCameraRadioGroupSelectedItemID;

public:
	GraphSceneUI();
	~GraphSceneUI();

	virtual void initGUI();
	void initDrawingModePanel();
	void initCamerasPanel();
	void initLightsPanel();
	void updateValues();

	void processGUI(GLUI_Control* ctrl);
	virtual void processKeyboard(unsigned char key, int x, int y);
};
