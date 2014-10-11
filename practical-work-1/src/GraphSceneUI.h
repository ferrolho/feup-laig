#pragma once

#include "CGFinterface.h"

class GraphSceneUI: public CGFinterface {
private:
	int drawingModeRadioGroupSelectedItemID;

public:
	GraphSceneUI();
	virtual ~GraphSceneUI();

	void initGUI();
	void initDrawingModePanel();
	void initCamerasPanel();
	void initLightsPanel();

	void processGUI(GLUI_Control* ctrl);
	void processKeyboard(unsigned char key, int x, int y);
};
