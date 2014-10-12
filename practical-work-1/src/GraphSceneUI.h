#pragma once

#include "CGFinterface.h"

class GraphSceneUI: public CGFinterface {
private:
	int drawingModeRadioGroupSelectedItemID;

public:
	GraphSceneUI();

	virtual void initGUI();
	void initDrawingModePanel();
	void initCamerasPanel();
	void initLightsPanel();

	//void processGUI(GLUI_Control* ctrl);
	virtual void processKeyboard(unsigned char key, int x, int y);
};
