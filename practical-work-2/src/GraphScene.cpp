#include "GraphScene.h"

#include "GraphSceneUI.h"
#include "Primitive.h"
#include "XMLParser.h"

int GraphScene::WIND = 10;
int GraphScene::FPS = 60;

GraphScene::GraphScene(const char* xmlPath) {
	globals = new Globals();
	cameras = new Cameras();
	lights = new Lights();
	graph = new SceneGraph();

	XMLParser(xmlPath, *globals, *cameras, *lights, graph);
	//setActiveCamera((*cameras->getCameras())[cameras->getActiveCameraID()]);

	lights->init();
}

GraphScene::~GraphScene() {
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
}

void GraphScene::clearBackground() {
	RGBA* bg = globals->getDrawing()->getBackground();
	glClearColor(bg->getR(), bg->getG(), bg->getB(), bg->getA());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

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
