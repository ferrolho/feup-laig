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

	/////////
	connection = new Connection();
	connection->send("initialize.\n");
	message = connection->receive();

	eximo = new Eximo((*graph->getNodes())["white-checker"],
			(*graph->getNodes())["black-checker"], message->getContent());
	cout << eximo->toString() << endl;
	//////////

	obj = new ExampleObject();
	materialAppearance = new CGFappearance();

	lights->init();
}

GraphScene::~GraphScene() {
	connection->quit();

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

	// move ready
	if (((GraphSceneUI*) iface)->destSelected) {
		// make move
		printf("making a move\n");

		string command = "move(";
		command.append(((GraphSceneUI*) iface)->srcCell.toString());
		command.append(", ");
		command.append(((GraphSceneUI*) iface)->destCell.toString());
		command.append(", ");
		command.append(eximo->toPrologString());
		command.append(").\n");

		connection->send(command);
		message = connection->receive();
		eximo->update(message);
		cout << eximo->toString() << endl;

		((GraphSceneUI*) iface)->srcSelected = false;
		((GraphSceneUI*) iface)->destSelected = false;
	}
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

void GraphScene::restartAnimations() {
	graph->getRoot()->restartAnimation();
}

void GraphScene::setActiveCamera(Camera* camera) {
	activeCamera = camera;
	cameras->setActiveCameraID(camera->getId());
}
