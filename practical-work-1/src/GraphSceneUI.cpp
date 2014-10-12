#include "GraphSceneUI.h"

#include "GraphScene.h"

enum uiIds {
	DRAWING_MODE_RADIO_GROUP
};

GraphSceneUI::GraphSceneUI() {
	drawingModeRadioGroupSelectedItemID = 0;
	drawingModePanel = NULL;
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
	//drawingModePanel = addPanel(text, 1);

	/*
	 GLUI_RadioGroup* drawingModeGroup = addRadioGroupToPanel(drawingModePanel,
	 &drawingModeRadioGroupSelectedItemID, DRAWING_MODE_RADIO_GROUP);

	 strcpy(text, "Point");
	 addRadioButtonToGroup(drawingModeGroup, text);
	 strcpy(text, "Line");
	 addRadioButtonToGroup(drawingModeGroup, text);
	 strcpy(text, "Fill");
	 addRadioButtonToGroup(drawingModeGroup, text);
	 */
}

void GraphSceneUI::initCamerasPanel() {

}

void GraphSceneUI::initLightsPanel() {

}
/*
 void GraphSceneUI::processGUI(GLUI_Control* ctrl) {
 switch (ctrl->user_id) {
 case DRAWING_MODE_RADIO_GROUP:
 switch (drawingModeRadioGroupSelectedItemID) {
 case 0:
 ((GraphScene*) scene)->setDrawingMode(GL_POINT);
 break;
 case 1:
 ((GraphScene*) scene)->setDrawingMode(GL_LINE);
 break;
 case 2:
 ((GraphScene*) scene)->setDrawingMode(GL_FILL);
 break;
 default:
 break;
 }
 break;
 default:
 break;
 };
 }

 */
void GraphSceneUI::processKeyboard(unsigned char key, int x, int y) {
	CGFinterface::processKeyboard(key, x, y);
}
