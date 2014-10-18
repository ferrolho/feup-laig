#include "GraphScene.h"

#include "Primitive.h"
#include "XMLParser.h"

GraphScene::GraphScene(const char* xmlPath) {
	globals = new Globals();
	cameras = new Cameras();
	lights = new Lights();
	graph = new SceneGraph();

	XMLParser(xmlPath, *globals, *lights, graph);

	lights->init();
}

GraphScene::~GraphScene() {
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
	globals->getLighting()->getEnabled() ?
			glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);

	if (globals->getLighting()->getDoubleSided())
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,
				globals->getLighting()->getDoubleSided());

	if (globals->getLighting()->getLocal())
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
				globals->getLighting()->getAmbient()->getRGBA());

	setUpdatePeriod(100);
}

void GraphScene::update(unsigned long sysTime) {
	// TODO will this be needed?
}

void GraphScene::display() {
	RGBA* bg = globals->getDrawing()->getBackground();
	glClearColor(bg->getR(), bg->getG(), bg->getB(), bg->getA());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, globals->getDrawing()->getMode());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//cameras->getCameras()[cameras->getActivedCamera()]->applyView();
	CGFscene::activeCamera->applyView();

	lights->update();
	lights->draw();

	axis.draw();

	graph->draw();

	glutSwapBuffers();
}
