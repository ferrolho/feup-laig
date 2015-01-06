#include "GraphSceneUI.h"

#include "CGFapplication.h"
#include "GraphScene.h"

enum uiIDs {
	DRAWING_MODE_RADIO_GROUP,
	SHADING_MODE_RADIO_GROUP,
	ACTIVE_CAMERA_RADIO_GROUP,
	WIND_SPINNER,
	ANIMATIONS_RESET_BUTTON,
	REVIEW_GAME,
	UNDO_BUTTON,
	SCOREBOARD_P1_INC,
	SCOREBOARD_P1_DEC,
	SCOREBOARD_P2_INC,
	SCOREBOARD_P2_DEC,
	RESTART_CLOCK,
	PAUSE_CLOCK
};

GraphSceneUI::GraphSceneUI() {
	initValuesUpdated = false;
	drawingModeRadioGroupSelectedItemID = 0;
	shadingModeRadioGroupSelectedItemID = 0;
	activeCameraRadioGroupSelectedItemID = 0;

	selectedAnotherCell = false;
	selectedCell = Point2D();
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

	addColumn();

	initShadersPanel();

	initAnimationsPanel();

	addColumn();

	initScoreboardPanel();

	addColumn();

	initClockPanel();
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

void GraphSceneUI::initAnimationsPanel() {
	char* text = new char[256];

	strcpy(text, "Animations");
	GLUI_Panel* animationsPanel = addPanel(text);

	strcpy(text, "Restart");
	addButtonToPanel(animationsPanel, text, ANIMATIONS_RESET_BUTTON);

	strcpy(text, "Review Game");
	addButtonToPanel(animationsPanel, text, REVIEW_GAME);

	strcpy(text, "Undo");
	addButtonToPanel(animationsPanel, text, UNDO_BUTTON);
}

void GraphSceneUI::initScoreboardPanel() {
	char* text = new char[256];

	strcpy(text, "Scoreboard");
	GLUI_Panel* scoreboardPanel = addPanel(text);

	strcpy(text, "Player1 Inc");
	addButtonToPanel(scoreboardPanel, text, SCOREBOARD_P1_INC);

	strcpy(text, "Player1 Dec");
	addButtonToPanel(scoreboardPanel, text, SCOREBOARD_P1_DEC);

	strcpy(text, "Player2 Inc");
	addButtonToPanel(scoreboardPanel, text, SCOREBOARD_P2_INC);

	strcpy(text, "Player2 Dec");
	addButtonToPanel(scoreboardPanel, text, SCOREBOARD_P2_DEC);
}

void GraphSceneUI::initClockPanel() {
	char* text = new char[256];

	strcpy(text, "Clock");
	GLUI_Panel* clockPanel = addPanel(text);

	strcpy(text, "Pause");
	addButtonToPanel(clockPanel, text, PAUSE_CLOCK);

	strcpy(text, "Restart");
	addButtonToPanel(clockPanel, text, RESTART_CLOCK);
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

		map<string, Camera*>::iterator it;
		int i;
		for (i = 0, it = cams->begin(); it != cams->end(); it++, i++) {
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

	case ANIMATIONS_RESET_BUTTON:
		((GraphScene*) scene)->restartAnimations();

		break;

	case REVIEW_GAME:
		((GraphScene*) scene)->reviewGame();

		break;

	case UNDO_BUTTON:
		((GraphScene*) scene)->undoMove();

		break;

	case SCOREBOARD_P1_INC:
		cout << "Incremento em Player 1!\n";
		((GraphScene*) scene)->getScoreboard()->setScoreboard(BLACK_PLAYER, INC);

		break;

	case SCOREBOARD_P1_DEC:
		cout << "Decremento em Player 1!\n";
		((GraphScene*) scene)->getScoreboard()->setScoreboard(BLACK_PLAYER, DEC);

		break;

	case SCOREBOARD_P2_INC:
		cout << "Incremento em Player 2!\n";
		((GraphScene*) scene)->getScoreboard()->setScoreboard(WHITE_PLAYER, INC);

		break;

	case SCOREBOARD_P2_DEC:
		cout << "Decremento em Player 2!\n";
		((GraphScene*) scene)->getScoreboard()->setScoreboard(WHITE_PLAYER, DEC);

		break;

	case PAUSE_CLOCK:
		cout << "Pause Clock!\n";
		((GraphScene*) scene)->getClockGame()->pauseClock();

		break;

	case RESTART_CLOCK:
		cout << "Restart Clock!\n";
		((GraphScene*) scene)->getClockGame()->setClockGame();

		break;

	default:
		break;
	}
}

void GraphSceneUI::processKeyboard(unsigned char key, int x, int y) {
	CGFinterface::processKeyboard(key, x, y);
}

// buffer to be used to store the hits during picking
const int BUFSIZE = 256;
GLuint selectBuf[BUFSIZE];

void GraphSceneUI::processMouse(int button, int state, int x, int y) {
	CGFinterface::processMouse(button, state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// TODO this could be more elaborate, e.g. only performing picking when
	// there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x, y);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		((GraphScene*) scene)->turnState = SELECTING_SRC;

		printf("restarting move.. pick a src cell\n");
	}
}

void GraphSceneUI::performPicking(int x, int y) {
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	// store current projection matrix to restore easily in the end with a pop
	glPushMatrix();

	// get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0,
			5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void GraphSceneUI::processHits(GLint hits, GLuint buffer[]) {
	GLuint* ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint* selected = NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i = 0; i < hits; i++) {
		int num = *ptr;

		ptr++;
		GLuint z1 = *ptr;

		ptr++;
		ptr++;
		if (z1 < mindepth && num > 0) {
			mindepth = z1;
			selected = ptr;
			nselected = num;
		}

		for (int j = 0; j < num; j++)
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected != NULL) {
		// this should be replaced by code handling the picked object's ID's (stored in "selected"),
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (unsigned i = 0; i < nselected; i++) {
			printf("%d ", selected[i]);
		}
		printf("\n");

		selectedCell.setX(selected[0]);
		selectedCell.setY(selected[1]);
		selectedAnotherCell = true;
	} else
		printf("Nothing selected while picking\n");
}
