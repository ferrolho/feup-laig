#include "GraphScene.h"
#include "Primitive.h"
#include "XMLParser.h"

GraphScene::GraphScene(const char* xmlPath) {
	graph = new SceneGraph;
	XMLParser(xmlPath, graph);

	init();
}

void GraphScene::init() {
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	initLights();

	setUpdatePeriod(100);
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

void GraphScene::update(unsigned long sysTime) {
	light0->update();
	//	light1->update();
	//	light2->update();
	//	light3->update();
}

void GraphScene::display() {
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
