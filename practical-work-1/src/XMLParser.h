#pragma once

#include <map>
#include <string>
#include <vector>
#include "Cylinder.h"
#include "Rectangle.h"
#include "Rotation.h"
#include "Scaling.h"
#include "SceneGraph.h"
#include "Sphere.h"
#include "tinyxml.h"
#include "Torus.h"
#include "Transform.h"
#include "Translation.h"
#include "Triangle.h"
using namespace std;

class XMLParser {
private:
	string rootid;
	map<string, Node*> nodes;

	void loadXMLFile(char* filename);
	void loadAnfElement();

	string assignAndValidate(TiXmlElement* element, string elementStr,
			string attribute, vector<string> candidates, string defaultValue);

	void parseGlobals();
	void parseGlobalsDrawing();
	void parseGlobalsCulling();
	void parseGlobalsLighting();

	void parseCameras();
	void parsePerspectiveCamera(TiXmlElement* element);
	void parseOrthoCamera(TiXmlElement* element);

	void parseLights();
	void parseLight(TiXmlElement* element);
	void parseLightComponents(TiXmlElement* element);

	void parseTextures();
	void parseTexture(TiXmlElement* element);

	void parseAppearances();
	void parseAppearance(TiXmlElement* element);
	void parseAppearanceComponents(TiXmlElement* element);

	void parseGraph();
	void parseNode(TiXmlElement* element);

	Matrix parseTransforms(TiXmlElement* element);
	Transform* parseTransform(TiXmlElement* element);
	Translation* parseTranslate(TiXmlElement* element);
	Rotation* parseRotate(TiXmlElement* element);
	Scaling* parseScale(TiXmlElement* element);

	void parseAppearanceRef(TiXmlElement* element);

	vector<Primitive*> parsePrimitives(TiXmlElement* element);
	Rectangle* parseRectangle(TiXmlElement* primitive);
	Triangle* parseTriangle(TiXmlElement* primitive);
	Cylinder* parseCylinder(TiXmlElement* primitive);
	Sphere* parseSphere(TiXmlElement* primitive);
	Torus* parseTorus(TiXmlElement* primitive);

	vector<string> parseDescendants(TiXmlElement* element);
	string parseNodeRef(TiXmlElement* element);

	void parseNodeDescendants(Node* node, map<string, Node*>* nodes);

protected:
	TiXmlDocument* doc;
	TiXmlElement* anfElement;
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearencesElement;
	TiXmlElement* graphElement;

public:
	XMLParser(char* filename, SceneGraph* graph);
	~XMLParser();

	static TiXmlElement* findChildByAttribute(TiXmlElement* parent,
			const char* attr, const char* val);
};
