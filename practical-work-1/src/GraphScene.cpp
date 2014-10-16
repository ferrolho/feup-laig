#include "GraphScene.h"

#include "Primitive.h"
#include "XMLParser.h"

GraphScene::GraphScene(const char* xmlPath) {
	globals = new Globals();
	graph = new SceneGraph();

	XMLParser(xmlPath, *globals, graph);

	initLights();
}

GraphScene::~GraphScene() {
}

void GraphScene::initLights() {
	float ambientNull[4] = { 0, 0, 0, 1 };
	float light0_pos[4] = { 4, 6.0, 1.0, 1.0 };
	float light1_pos[4] = { 0, 0, -4.0, 1.0 };
	float white[4] = { 1, 1, 1, 1 };

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setSpecular(white);
	light0->setAmbient(ambientNull);
	light0->enable();

	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setSpecular(white);
	light1->setAmbient(ambientNull);
	light1->enable();
}

void GraphScene::init() {

	glEnable(GL_NORMALIZE);

	// globals > drawing
	glPolygonMode(GL_FRONT_AND_BACK, globals->getDrawing()->getMode());
	glShadeModel(globals->getDrawing()->getShading());

	// globals > culling
	if (globals->getCulling()->getFace() == GL_NONE)
		glDisable(GL_CULL_FACE);
	else {
		glEnable(GL_CULL_FACE);
		glCullFace(globals->getCulling()->getFace());
		glFrontFace(globals->getCulling()->getOrder());
	}

	// globals > lighting
	if (globals->getLighting()->getEnabled()) {
		glEnable(GL_LIGHTING);

		if (globals->getLighting()->getDoubleSided())
			glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,
					globals->getLighting()->getDoubleSided());

		if (globals->getLighting()->getLocal())
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
					globals->getLighting()->getAmbient()->getRGBA());
	} else {
		glDisable(GL_LIGHTING);
	}

	setUpdatePeriod(100);
}

void GraphScene::update(unsigned long sysTime) {
	light0->update();
	light1->update();
	//	light2->update();
	//	light3->update();
}

void GraphScene::display() {
	RGBA* bg = globals->getDrawing()->getBackground();
	glClearColor(bg->getR(), bg->getG(), bg->getB(), bg->getA());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, drawingMode);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CGFscene::activeCamera->applyView();

	light0->draw();
	light1->draw();

	axis.draw();

	graph->draw();

	glutSwapBuffers();
}

void GraphScene::setDrawingMode(GLenum mode) {
	drawingMode = mode;
}
