#pragma once

#include <vector>
#include <string>
#include "TinyXML/tinyxml.h"
using namespace std;

class XMLParser {
private:
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

	void parseTransforms(TiXmlElement* element);
	void parseTransform(TiXmlElement* element);
	void parseTranslate(TiXmlElement* element);
	void parseRotate(TiXmlElement* element);
	void parseScale(TiXmlElement* element);

	void parseAppearanceRef(TiXmlElement* element);

	void parsePrimitives(TiXmlElement* element);
	void parseRectangle(TiXmlElement* element);
	void parseTriangle(TiXmlElement* element);
	void parseCylinder(TiXmlElement* element);
	void parseSphere(TiXmlElement* element);
	void parseTorus(TiXmlElement* element);

	void parseDescendants(TiXmlElement* element);
	void parseNodeRef(TiXmlElement* element);

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
	XMLParser(char* filename);
	~XMLParser();

	static TiXmlElement* findChildByAttribute(TiXmlElement* parent,
			const char* attr, const char* val);
};
