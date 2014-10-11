#include "GraphScene.h"
#include "Primitive.h"
#include "XMLParser.h"

GraphScene::GraphScene(const char* xmlPath) {
	globals = new Globals();
	graph = new SceneGraph();

	XMLParser(xmlPath, *globals, graph);

	initLights();
}

void GraphScene::initLights() {
	// enables lighting computations
	glEnable(GL_LIGHTING);

	// sets up some lighting parameters, computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	float ambientNull[4] = { 0, 0, 0, 1 };
	float light0_pos[4] = { 4, 6.0, 1.0, 1.0 };
	float yellow[4] = { 1, 1, 0, 1 };

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setSpecular(yellow);
	light0->setAmbient(ambientNull);
	light0->enable();
}

void GraphScene::init() {
	glEnable(GL_NORMALIZE);

	if (globals->getDrawing()->getMode().compare("point") == 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	else if (globals->getDrawing()->getMode().compare("line") == 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (globals->getDrawing()->getMode().compare("fill") == 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (globals->getDrawing()->getShading().compare("flat") == 0)
		glShadeModel(GL_FLAT);
	else if (globals->getDrawing()->getShading().compare("gouraud") == 0)
		glShadeModel(GL_SMOOTH);

	initLights();

	setUpdatePeriod(100);
}

void GraphScene::update(unsigned long sysTime) {
	light0->update();
	//	light1->update();
	//	light2->update();
	//	light3->update();
}

void GraphScene::display() {
	RGBA* bg = globals->getDrawing()->getBackground();
	glClearColor(bg->getR(), bg->getG(), bg->getB(), bg->getA());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CGFscene::activeCamera->applyView();

	light0->draw();

	axis.draw();

	graph->draw();

	glutSwapBuffers();
}

GraphScene::~GraphScene() {

}
