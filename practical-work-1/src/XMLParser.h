#pragma once

#include <map>
#include <string>
#include <vector>
#include "Cylinder.h"
#include "Globals.h"
#include "Light.h"
#include "Lights.h"
#include "SceneGraph.h"
#include "Rectangle.h"
#include "Rotation.h"
#include "Scaling.h"
#include "SceneGraph.h"
#include "Sphere.h"
#include "SpotLight.h"
#include "tinyxml.h"
#include "Torus.h"
#include "Transform.h"
#include "Translation.h"
#include "Triangle.h"
#include "Texture.h"
#include "Appearance.h"
#include "Components.h"
#include "Cameras.h"

using namespace std;

class XMLParser {
public:
	XMLParser(const char* filename, Globals& globals, Cameras& cameras,
			Lights& lights, SceneGraph* graph);
	~XMLParser();

	static TiXmlElement* findChildByAttribute(TiXmlElement* parent,
			const char* attr, const char* val);

protected:
	TiXmlDocument* doc;
	TiXmlElement* anfElement;
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearencesElement;
	TiXmlElement* graphElement;

private:
	string rootid;
	map<string, Node*> nodes;
	map<string, Texture*> textures;
	map<string, Appearance*> appearances;
	map<string, Camera*> cameras;

	void loadXMLFile(const char* filename);
	void loadAnfElement();

	string assignAndValidate(TiXmlElement* element, const string& elementStr,
			const string& attribute, const vector<string>& candidates,
			const string& defaultValue);

	Globals* parseGlobals();
	Drawing* parseGlobalsDrawing();
	Culling* parseGlobalsCulling();
	Lighting* parseGlobalsLighting();

	Cameras* parseCameras();
	Perspective* parsePerspectiveCamera(TiXmlElement* element);
	Ortho* parseOrthoCamera(TiXmlElement* element);

	Lights* parseLights();
	Light* parseLight(TiXmlElement* element);
	Components* parseLightComponents(TiXmlElement* element);

	void parseTextures();
	Texture* parseTexture(TiXmlElement* element);

	void parseAppearances();
	Appearance* parseAppearance(TiXmlElement* element);
	Components* parseAppearanceComponents(TiXmlElement* element);

	void parseGraph(SceneGraph* graph);
	void parseNode(TiXmlElement* element);

	Matrix parseTransforms(TiXmlElement* element);
	Transform* parseTransform(TiXmlElement* element);
	Translation* parseTranslate(TiXmlElement* element);
	Rotation* parseRotate(TiXmlElement* element);
	Scaling* parseScale(TiXmlElement* element);

	Appearance* parseAppearanceRef(TiXmlElement* element);

	const vector<Primitive*> parsePrimitives(TiXmlElement* element,
			Texture* texture = NULL);
	Rectangle* parseRectangle(TiXmlElement* primitive, Texture* texture = NULL);
	Triangle* parseTriangle(TiXmlElement* primitive, Texture* texture = NULL);
	Cylinder* parseCylinder(TiXmlElement* primitive);
	Sphere* parseSphere(TiXmlElement* primitive);
	Torus* parseTorus(TiXmlElement* primitive);

	const vector<string> parseDescendants(TiXmlElement* element);
	const string parseNodeRef(TiXmlElement* element);

	void parseNodeDescendants(Node* node);
	void parseNodeDescendants(Node* node, unsigned int level);
};
