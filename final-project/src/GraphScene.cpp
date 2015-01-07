#include "GraphScene.h"

#include "Primitive.h"
#include "XMLParser.h"

#include "Connection.h"

int GraphScene::WIND = 10;
int GraphScene::FPS = 60;

#include "ExampleObject.h"

GraphScene::GraphScene(const char* xmlPath) {
	connection = new Connection();

	globals = new Globals();
	cameras = new Cameras();
	lights = new Lights();
	graph = new SceneGraph();
	scoreboard = new Scoreboard();

	// parse anf file
	XMLParser(xmlPath, *globals, *cameras, *lights, appearances, graph,
			scoreboard);

	// add player camera
	playerCam = new LockedPerspective("Player", 1, 100, 35,
			new Point3D(0, 25, 25), new Point3D(0, 0, 0));
	cameras->add(playerCam);
	setActiveCamera(playerCam);

	// add clock
	gameChronometer = new ClockGame((*graph->getNodes())["game-clock"],
			new Clock(appearances["clock"], appearances["clockhand"]));

	scoreboard->setNode((*graph->getNodes())["scoreboard"]);
	scoreboard->init();

	message = connection->initialize();

	eximo = new Eximo(graph, scoreboard, message->getContent());

	turnState = CHECK_IF_GAME_IS_OVER;
	turnType = FREE_TURN;

	obj = new ExampleObject();
	materialAppearance = new CGFappearance();

	lights->init();
}

GraphScene::~GraphScene() {
	connection->terminate();

	delete (materialAppearance);
	delete (obj);
}

unsigned long lastTime;

void GraphScene::init() {
	// TODO refactor this
	lastTime = 0;

	glEnable(GL_NORMALIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// globals > drawing
	glPolygonMode(GL_FRONT_AND_BACK, globals->getDrawing()->getMode());

	// globals > culling
	if (globals->getCulling()->getFace() == GL_NONE)
		glDisable(GL_CULL_FACE);
	else {
		glEnable(GL_CULL_FACE);
		glCullFace(globals->getCulling()->getFace());
		glFrontFace(globals->getCulling()->getOrder());
	}

	// globals > lighting
	globals->getLighting()->getEnabled() ?
			glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);

	if (globals->getLighting()->getDoubleSided())
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,
				globals->getLighting()->getDoubleSided());

	if (globals->getLighting()->getLocal())
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
				globals->getLighting()->getAmbient()->getRGBA());

	// setting update period
	setUpdatePeriod(1000.0 / FPS);
}

void GraphScene::update(unsigned long sysTime) {
	((GraphSceneUI*) iface)->updateInitValues();

	glShadeModel(globals->getDrawing()->getShading());

	graph->update(sysTime);

	gameChronometer->update(sysTime);

	scoreboard->update(sysTime);

	eximo->update(sysTime);

	if (!lastTime)
		lastTime = sysTime;

	unsigned long deltaTime = sysTime - lastTime;
	lastTime = sysTime;

	playerCam->update(deltaTime);

	string command;

	switch (turnState) {
	case CHECK_IF_GAME_IS_OVER:
		printf("check if game is over\n");

		command = "gameOver(";
		command.append(eximo->toPrologString());
		command.append(").\n");

		connection->send(command);
		message = connection->receive();

		if (message->isValid()) {
			printf("game is over. winner: %s\n",
					eximo->getCurrentPlayer().c_str());
			turnState = GAME_OVER;
		} else {
			printf("game is NOT over\n");
			turnState = SELECTING_SRC;
		}

		break;

	case SELECTING_SRC:
		if (!((GraphSceneUI*) iface)->selectedAnotherCell)
			break;

		// check source cell ownership
		printf("check source cell ownership\n");

		command = "validateSrc(";
		command.append(((GraphSceneUI*) iface)->selectedCell.toString());
		command.append(", _, _ , ");
		command.append(eximo->toPrologString());
		command.append(").\n");

		connection->send(command);
		message = connection->receive();

		if (message->isValid()) {
			eximo->srcCell = ((GraphSceneUI*) iface)->selectedCell;
			turnState = SELECTING_DEST;
			printf("valid src :D\n");
		} else
			printf("invalid src, select another\n");

		break;

	case SELECTING_DEST:
		if (!((GraphSceneUI*) iface)->selectedAnotherCell)
			break;

		// make move
		printf("making a move\n");

		switch (turnType) {
		case FREE_TURN:
			command = "move(";
			command.append(eximo->srcCell.toString());
			command.append(", ");
			break;

		case MANDATORY_JUMP:
			command = "jump(";
			command.append(eximo->srcCell.toString());
			command.append(", ");
			break;

		case MANDATORY_CAPTURE:
			command = "capture(";
			command.append(eximo->srcCell.toString());
			command.append(", ");
			break;

		case PLACE_2_CHECKERS:
			command = "place2Checkers(";
			break;

		case PLACE_1_CHECKER:
			command = "place1Checker(";
			break;
		}

		command.append(((GraphSceneUI*) iface)->selectedCell.toString());
		command.append(", ");
		command.append(eximo->toPrologString());
		command.append(").\n");

		connection->send(command);
		message = connection->receive();

		if (message->isValid()) {
			eximo->destCell = ((GraphSceneUI*) iface)->selectedCell;
			printf("valid dest :D\n\n");

			if (eximo->historyIsEmpty())
				eximo->updateTempGame();

			eximo->moveChecker(eximo->srcCell, eximo->destCell);
			eximo->update(message);

			switch (message->getType()) {
			case MOVE_OK:
				turnState = CHECK_IF_GAME_IS_OVER;
				turnType = FREE_TURN;

				printf("@@ move finished. updating history!\n");
				eximo->saveTempGameToHistory();

				static_cast<LockedPerspective*>((*cameras->getCameras())["Player"])->togglePlayer();

				break;

			case CONTINUE_JUMP:
				eximo->srcCell = eximo->destCell;
				turnType = MANDATORY_JUMP;
				break;

			case CONTINUE_CAPTURE:
				eximo->srcCell = eximo->destCell;
				turnType = MANDATORY_CAPTURE;
				break;

			case RECEIVE_2_CHECKERS:
				turnType = PLACE_2_CHECKERS;
				break;

			case RECEIVE_1_CHECKER:
				turnType = PLACE_1_CHECKER;
				break;

			default:
				break;
			}
		} else
			printf("invalid dest, select another\n");

		break;

	case GAME_OVER:
		// TODO do something here
		break;

	default:
		break;
	}

	((GraphSceneUI*) iface)->selectedAnotherCell = false;
}

void GraphScene::clearBackground() {
	RGBA* bg = globals->getDrawing()->getBackground();
	glClearColor(bg->getR(), bg->getG(), bg->getB(), bg->getA());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const int NUM_ROWS = 8;
const int NUM_COLS = 8;

void GraphScene::display() {
	clearBackground();
	glPolygonMode(GL_FRONT_AND_BACK, globals->getDrawing()->getMode());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cameras->getActiveCamera()->applyView();
	//CGFscene::activeCamera->applyView();

	GLint currentRenderMode;
	glGetIntegerv(GL_RENDER_MODE, &currentRenderMode);

	currentRenderMode == GL_RENDER ? displayRenderMode() : displaySelectMode();

	glutSwapBuffers();
}

void GraphScene::displayRenderMode() {
	lights->update();
	lights->draw();

	axis.draw();

	graph->draw();

	gameChronometer->draw();

	scoreboard->draw();

	eximo->draw();
}

void GraphScene::displaySelectMode() {
	// picking example, the important parts are the gl*Name functions
	// and the code in the associated PickInterface class
	materialAppearance->apply();

	// Load a default name
	glPushName(-1);

	glTranslatef(-10, 0.255, -10);
	glRotatef(-90, 1, 0, 0);

	for (int row = 0; row < NUM_ROWS; row++) {
		glPushMatrix();

		glTranslatef(0, row * -2.5, 0);

		glLoadName(row);

		for (int column = 0; column < NUM_COLS; column++) {
			glPushMatrix();

			glTranslatef(column * 2.5, 0, 0);
			glTranslatef(0.25, -0.25, 0);

			glPushName(column);
			obj->draw();
			glPopName();

			glPopMatrix();
		}

		glPopMatrix();
	}
}

Globals* GraphScene::getGlobals() {
	return globals;
}

Cameras* GraphScene::getCameras() {
	return cameras;
}

Lights* GraphScene::getLights() {
	return lights;
}

SceneGraph* GraphScene::getGraph() {
	return graph;
}

Scoreboard* GraphScene::getScoreboard() {
	return scoreboard;
}

ClockGame* GraphScene::getClockGame() {
	return gameChronometer;
}

void GraphScene::restartAnimations() {
	graph->getRoot()->restartAnimation();
}

void GraphScene::undoMove() {
	eximo->popHistory();
	turnState = CHECK_IF_GAME_IS_OVER;
	turnType = FREE_TURN;
}

void GraphScene::setActiveCamera(Camera* camera) {
	activeCamera = camera;
	cameras->setActiveCameraID(camera->getId());
}

void GraphScene::setActiveTheme(int activeTheme) {
	if (activeTheme == CLASSIC) {
		// board structure
		(*graph->getNodes())["game-board"]->setAppearance(appearances["wood"]);

		// board chess texture
		(*graph->getNodes())["board-top"]->setAppearance(
				appearances["wooden-board"]);

		// drawers
		(*graph->getNodes())["board-drawer-1"]->setAppearance(
				appearances["drawer-wooden"]);

		// clock
		(*graph->getNodes())["game-clock"]->setAppearance(appearances["wood"]);

		// scoreboard
		(*graph->getNodes())["scoreboard"]->setAppearance(appearances["wood"]);

		eximo->toggleCheckerNode((*graph->getNodes())["white-checker"],
				appearances["white-marble"], appearances["black-marble"]);

	} else if (activeTheme == AVIATOR) {
		// board structure
		(*graph->getNodes())["game-board"]->setAppearance(appearances["metal"]);

		// board chess texture
		(*graph->getNodes())["board-top"]->setAppearance(
				appearances["blue-board"]);

		// drawers
		(*graph->getNodes())["board-drawer-1"]->setAppearance(
				appearances["drawer-metal"]);

		// clock
		(*graph->getNodes())["game-clock"]->setAppearance(
				appearances["dark-metal"]);

		// scoreboard
		(*graph->getNodes())["scoreboard"]->setAppearance(
				appearances["dark-metal"]);

		// pieces
		eximo->toggleCheckerNode((*graph->getNodes())["airplane"],
				appearances["white-marble"], appearances["black-marble"]);
	}
}

void GraphScene::reviewGame() {
	if (eximo->reviewingGame) {
		eximo->reviewingGame = false;
	} else if (!eximo->historyIsEmpty()) {
		eximo->reviewingGame = true;
		eximo->reviewStep = 0;
		eximo->lastTime = 0;
		eximo->reviewFrameTime = 0;
	}
}
