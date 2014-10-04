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
	void parseCamerasPerspective();
	void parseCamerasOrtho();

	void parseLights();
	void parseLightsLight();

	void parseTextures();
	void parseTexturesTexture();

	void parseAppearances();
	void parseAppearancesAppearance();

	void parseGraph();

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
