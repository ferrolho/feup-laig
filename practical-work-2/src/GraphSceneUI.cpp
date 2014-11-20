#include "GraphSceneUI.h"

#include "CGFapplication.h"
#include "GraphScene.h"

enum uiIDs {
	DRAWING_MODE_RADIO_GROUP,
	SHADING_MODE_RADIO_GROUP,
	ACTIVE_CAMERA_RADIO_GROUP,
	WIND_SPINNER
};

GraphSceneUI::GraphSceneUI() {
	initValuesUpdated = false;
	drawingModeRadioGroupSelectedItemID = 0;
	shadingModeRadioGroupSelectedItemID = 0;
	activeCameraRadioGroupSelectedItemID = 0;
}

GraphSceneUI::~GraphSceneUI() {
}

void GraphSceneUI::initGUI() {
	initDrawingModePanel();

	addColumn();

	initShadingModePanel();

	addColumn();

	initCamerasPanel();

	addColumn();

	initLightsPanel();

	initShadersPanel();
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

void GraphSceneUI::initShadingModePanel() {
	char* text = new char[256];

	strcpy(text, "Shading Mode");
	GLUI_Panel* shadingModePanel = addPanel(text);

	GLUI_RadioGroup* shadingModeGroup = addRadioGroupToPanel(shadingModePanel,
			&shadingModeRadioGroupSelectedItemID, SHADING_MODE_RADIO_GROUP);

	strcpy(text, "Flat");
	addRadioButtonToGroup(shadingModeGroup, text);
	strcpy(text, "Gouraud");
	addRadioButtonToGroup(shadingModeGroup, text);
}

void GraphSceneUI::initCamerasPanel() {
	char* text = new char[256];

	strcpy(text, "Cameras");
	GLUI_Panel* camerasPanel = addPanel(text);

	GLUI_RadioGroup* camerasGroup = addRadioGroupToPanel(camerasPanel,
			&activeCameraRadioGroupSelectedItemID, ACTIVE_CAMERA_RADIO_GROUP);

	map<string, Camera*>* cameras =
			((GraphScene*) scene)->getCameras()->getCameras();
	map<string, Camera*>::iterator it;

	for (it = cameras->begin(); it != cameras->end(); it++) {
		strcpy(text, it->second->getId().c_str());
		addRadioButtonToGroup(camerasGroup, text);
	}
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

void GraphSceneUI::initShadersPanel() {
	char* text = new char[256];

	strcpy(text, "Shaders");
	GLUI_Panel* shadersPanel = addPanel(text);

	strcpy(text, "Wind");
	addSpinnerToPanel(shadersPanel, text, 2, &GraphScene::WIND, WIND_SPINNER);
}

void GraphSceneUI::updateInitValues() {
	if (initValuesUpdated)
		return;

	drawingModeRadioGroupSelectedItemID =
			((GraphScene*) scene)->getGlobals()->getDrawing()->getMode() - GL_POINT;

	shadingModeRadioGroupSelectedItemID =
			((GraphScene*) scene)->getGlobals()->getDrawing()->getShading() - GL_FLAT;

	int i = 0;
	Cameras* cams = ((GraphScene*) scene)->getCameras();
	for (map<string, Camera*>::iterator it = cams->getCameras()->begin();
			it != cams->getCameras()->end(); it++, i++) {
		if ((*it).first.compare(cams->getActiveCameraID()) == 0) {
			activeCameraRadioGroupSelectedItemID = i;
			break;
		}
	}

	initValuesUpdated = true;
}

void GraphSceneUI::processGUI(GLUI_Control* ctrl) {
	switch (ctrl->user_id) {
	case DRAWING_MODE_RADIO_GROUP:
		((GraphScene*) scene)->getGlobals()->getDrawing()->setMode(
		GL_POINT + drawingModeRadioGroupSelectedItemID);
		break;
	case SHADING_MODE_RADIO_GROUP:
		((GraphScene*) scene)->getGlobals()->getDrawing()->setShading(
		GL_FLAT + shadingModeRadioGroupSelectedItemID);
		break;
	case ACTIVE_CAMERA_RADIO_GROUP: {
		map<string, Camera*>* cams =
				((GraphScene*) scene)->getCameras()->getCameras();

		int i = 0;
		for (map<string, Camera*>::iterator it = cams->begin();
				it != cams->end(); it++, i++) {
			if (i == activeCameraRadioGroupSelectedItemID) {
				((GraphScene*) scene)->setActiveCamera((*it).second);
				break;
			}
		}

		CGFapplication::activeApp->forceRefresh();

		break;
	}
	case WIND_SPINNER:
		((GraphScene*) scene)->WIND = ctrl->float_val;
		break;
	default:
		break;
	};
}

void GraphSceneUI::processKeyboard(unsigned char key, int x, int y) {
	CGFinterface::processKeyboard(key, x, y);
}
