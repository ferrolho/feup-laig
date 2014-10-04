#pragma once

#include "TinyXML/tinyxml.h"

class XMLParser {
private:
	void loadXMLFile(char* filename);
	void loadAnfElement();
	void parseGlobals();
	void parseCameras();
	void parseLights();
	void parseTextures();
	void parseAppearances();
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
