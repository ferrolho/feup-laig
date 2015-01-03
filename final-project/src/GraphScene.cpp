#include "GraphScene.h"

#include "Primitive.h"
#include "XMLParser.h"

#include "Connection.h"

int GraphScene::WIND = 10;
int GraphScene::FPS = 60;

#include "ExampleObject.h"

GraphScene::GraphScene(const char* xmlPath) {
	globals = new Globals();
	cameras = new Cameras();
	lights = new Lights();
	graph = new SceneGraph();

	XMLParser(xmlPath, *globals, *cameras, *lights, graph);
	//setActiveCamera((*cameras->getCameras())[cameras->getActiveCameraID()]);

	//graph->initScoreboard();
	graph->setScoreboard("player1", "inc");

	/////////
	connection = new Connection();
	message = connection->initialize();

	eximo = new Eximo((*graph->getNodes())["white-checker"],
			(*graph->getNodes())["black-checker"], message->getContent());
	//////////

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

void GraphScene::init() {
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
			srcCell = ((GraphSceneUI*) iface)->selectedCell;
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
			break;

		case MANDATORY_JUMP:
			command = "jump(";
			break;

		case MANDATORY_CAPTURE:
			command = "capture(";
			break;
		}

		command.append(srcCell.toString());
		command.append(", ");
		command.append(((GraphSceneUI*) iface)->selectedCell.toString());
		command.append(", ");
		command.append(eximo->toPrologString());
		command.append(").\n");

		connection->send(command);
		message = connection->receive();

		if (message->isValid()) {
			destCell = ((GraphSceneUI*) iface)->selectedCell;
			printf("valid dest :D\n");

			eximo->update(message);
			cout << eximo->toString() << endl;

			if (message->getType() == CONTINUE_JUMP) {
				srcCell = destCell;
				turnType = MANDATORY_JUMP;

				printf("continuing jump......\n");
			} else if (message->getType() == CONTINUE_CAPTURE) {
				srcCell = destCell;
				turnType = MANDATORY_CAPTURE;

				printf("continuing capture......\n");
			} else {
				turnState = CHECK_IF_GAME_IS_OVER;
				turnType = FREE_TURN;
			}
		} else
			printf("invalid dest, select another\n");

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

	//cameras->getActiveCamera()->applyView();
	CGFscene::activeCamera->applyView();

	lights->update();
	lights->draw();

	axis.draw();

	graph->draw();

	eximo->draw();

	// ---- BEGIN feature demos
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
	// ---- END feature demos

	glutSwapBuffers();
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

void GraphScene::restartAnimations() {
	graph->getRoot()->restartAnimation();
}

void GraphScene::setActiveCamera(Camera* camera) {
	activeCamera = camera;
	cameras->setActiveCameraID(camera->getId());
}

void GraphScene::setGameScore(string player, string mode) {
	cout << "ENTREI\n";

	cout << graph->toString();

	if ((*graph->getNodes())["white-checker"])
		cout << "ID: " /*<< (*graph->getNodes())["leaf-111"]->getID()*/ << endl;
	else
		cout << "NULL\n";

	//graph->setScoreboard(player, mode);
}
