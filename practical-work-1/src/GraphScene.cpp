#include "GraphScene.h"

#include "XMLParser.h"

GraphScene::GraphScene(char* xmlPath) {
	new XMLParser(xmlPath);
}

void GraphScene::init() {

}

void GraphScene::update(unsigned long sysTime) {

}

void GraphScene::display() {

}

GraphScene::~GraphScene() {

}
