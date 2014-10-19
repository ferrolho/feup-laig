#include "GraphSceneUI.h"

#include "glui.h"
#include "GraphScene.h"

enum uiIDs {
	DRAWING_MODE_RADIO_GROUP, ACTIVE_CAMERA_RADIO_GROUP
};

enum camerasIDs {
	LIGHT0
};

GraphSceneUI::GraphSceneUI() {
	drawingModeRadioGroupSelectedItemID = 0;
	activeCameraRadioGroupSelectedItemID = 0;
}

GraphSceneUI::~GraphSceneUI() {
}

void GraphSceneUI::initGUI() {
	initDrawingModePanel();

	addColumn();

	initCamerasPanel();

	addColumn();

	initLightsPanel();
}

void GraphSceneUI::initDrawingModePanel() {
	char* text = new char[256];

	strcpy(text, "Drawing Mode");
	GLUI_Panel* drawingModePanel = addPanel(text);

	GLUI_RadioGroup* drawingModeGroup = addRadioGroupToPanel(drawingModePanel,
			&drawingModeRadioGroupSelectedItemID, DRAWING_MODE_RADIO_GROUP);

	strcpy(text, "Point");
	addRadioButtonToGroup(drawingModeGroup, text);
	strcpy(text, "Line");
	addRadioButtonToGroup(drawingModeGroup, text);
	strcpy(text, "Fill");
	addRadioButtonToGroup(drawingModeGroup, text);
}

void GraphSceneUI::initCamerasPanel() {
	char* text = new char[256];

	strcpy(text, "Active Camera");
	//GLUI_Panel* camerasPanel = addPanel(text);

	//GLUI_RadioGroup* camerasGroup = addRadioGroupToPanel(camerasPanel, &activeCameraRadioGroupSelectedItemID, ACTIVE_CAMERA_RADIO_GROUP);

	//TODO cameras ui
	//for (int i = 0; i < cameras.size(); i++) {
	//strcpy(text, "Point");
	//addRadioButtonToGroup(camerasGroup, text);
	//}
}

void GraphSceneUI::initLightsPanel() {
	char* text = new char[256];

	strcpy(text, "Lights");
	GLUI_Panel* lightsPanel = addPanel(text);

	vector<Light*>* lights = ((GraphScene*) scene)->getLights()->getLights();

	for (unsigned int i = 0; i < lights->size(); i++) {
		Light* light = (*lights)[i];

		strcpy(text, light->getStrID().c_str());
		addCheckboxToPanel(lightsPanel, text, light->getEnabled());
	}
}

void GraphSceneUI::updateValues() {
	drawingModeRadioGroupSelectedItemID =
			((GraphScene*) scene)->getGlobals()->getDrawing()->getMode() - GL_POINT;
}

void GraphSceneUI::processGUI(GLUI_Control* ctrl) {
	switch (ctrl->user_id) {
	case DRAWING_MODE_RADIO_GROUP:
		((GraphScene*) scene)->getGlobals()->getDrawing()->setMode(
		GL_POINT + drawingModeRadioGroupSelectedItemID);
		break;
	default:
		break;
	};
}

void GraphSceneUI::processKeyboard(unsigned char key, int x, int y) {
	CGFinterface::processKeyboard(key, x, y);
}
