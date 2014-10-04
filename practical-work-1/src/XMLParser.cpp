#include "XMLParser.h"

#include "Utilities.h"

XMLParser::XMLParser(char* filename) {
	loadXMLFile(filename);

	loadAnfElement();

	parseGlobals();
	parseCameras();
	parseLights();
	parseTextures();
	parseAppearances();
	parseGraph();
}

void XMLParser::loadXMLFile(char* filename) {
	doc = new TiXmlDocument(filename);
	bool loadOkay = doc->LoadFile();
	if (!loadOkay) {
		printf("ERROR: could not load file '%s'. Error='%s'. Exiting.\n",
				filename, doc->ErrorDesc());
		exit(1);
	}
}
void XMLParser::loadAnfElement() {
	anfElement = doc->FirstChildElement("anf");
	if (anfElement == NULL) {
		printf("ERROR: main anf block element not found. Exiting.\n");
		exit(1);
	}
}

string XMLParser::assignAndValidate(TiXmlElement* element, string elementStr,
		string attribute, vector<string> candidates, string defaultValue) {
	// read attribute from xml
	string str = element->Attribute(attribute.c_str());

	// look for a match between the xml attribute and any element of the list
	bool matchFound = false;
	foreach (candidates, it)
		if (str.compare(*it) == 0) {
			matchFound = true;
			break;
		}

	// if no match found, assign the default value
	if (!matchFound) {
		printf("WARNING: invalid %s > %s. Using default: %s.\n",
				elementStr.c_str(), attribute.c_str(), defaultValue.c_str());
		str = defaultValue;
	}

	return str;
}

void XMLParser::parseGlobals() {
	globalsElement = anfElement->FirstChildElement("globals");

	if (globalsElement) {
		printf("processing globals:\n");
		parseGlobalsDrawing();
		parseGlobalsCulling();
		parseGlobalsLighting();
	} else {
		printf("WARNING: globals block not found. Using defaults.\n");

		// TODO add default values here
	}
}

void XMLParser::parseGlobalsDrawing() {
	string mode, shading;
	float background[4];

	TiXmlElement* drawingElement = globalsElement->FirstChildElement("drawing");

	if (drawingElement) {
		vector<string> candidates;

		// --- mode --- //
		candidates.clear();
		candidates.push_back("fill");
		candidates.push_back("line");
		candidates.push_back("point");
		mode = assignAndValidate(drawingElement, "drawing", "mode", candidates,
				candidates[0]);

		// --- shading --- //
		candidates.clear();
		candidates.push_back("flat");
		candidates.push_back("gouraud");
		shading = assignAndValidate(drawingElement, "drawing", "shading",
				candidates, candidates[0]);

		// --- background --- //
		char* valString = NULL;
		valString = (char*) drawingElement->Attribute("background");
		if (!valString
				|| sscanf(valString, "%f %f %f %f", &background[0],
						&background[1], &background[2], &background[3]) != 4) {
			printf(
					"WARNING: could not parse drawing > background. Using defaults.\n");
			background[0] = background[1] = background[2] = 0;
			background[3] = 1;
		}
	} else {
		printf("WARNING: drawing block not found. Using defaults.\n");
		mode = "fill";
		shading = "flat";
		background[0] = background[1] = background[2] = 0;
		background[3] = 1;
	}

	printf("  drawing:\n");
	printf("    mode value [fill|line|point]: %s\n", mode.c_str());
	printf("    shading value [flat|gouraud]: %s\n", shading.c_str());
	printf("    background values [RGBA]: %f %f %f %f\n", background[0],
			background[1], background[2], background[3]);
}

void XMLParser::parseGlobalsCulling() {
	string face, order;

	TiXmlElement* cullingElement = globalsElement->FirstChildElement("culling");

	if (cullingElement) {
		vector<string> candidates;

		// --- face --- //
		candidates.clear();
		candidates.push_back("none");
		candidates.push_back("back");
		candidates.push_back("front");
		candidates.push_back("both");
		face = assignAndValidate(cullingElement, "culling", "face", candidates,
				candidates[1]);

		// --- order --- //
		candidates.clear();
		candidates.push_back("ccw");
		candidates.push_back("cw");
		order = assignAndValidate(cullingElement, "culling", "order",
				candidates, candidates[0]);
	} else {
		printf("WARNING: culling block not found. Using defaults.\n");
		face = "back";
		order = "ccw";
	}

	printf("  culling:\n");
	printf("    face value [none|back|front|both]: %s\n", face.c_str());
	printf("    order value [ccw|cw]: %s\n", order.c_str());
}

void XMLParser::parseGlobalsLighting() {
	string doublesided, local, enabled;
	float ambient[4];

	TiXmlElement* lightingElement = globalsElement->FirstChildElement(
			"lighting");

	if (lightingElement) {
		vector<string> candidates;
		candidates.push_back("false");
		candidates.push_back("true");

		// --- doublesided --- //
		doublesided = assignAndValidate(lightingElement, "lighting",
				"doublesided", candidates, candidates[1]);

		// --- local --- //
		local = assignAndValidate(lightingElement, "lighting", "local",
				candidates, candidates[0]);

		// --- enabled --- //
		enabled = assignAndValidate(lightingElement, "lighting", "enabled",
				candidates, candidates[1]);

		// --- ambient --- //
		char* valString = NULL;
		valString = (char*) lightingElement->Attribute("ambient");
		if (!valString
				|| sscanf(valString, "%f %f %f %f", &ambient[0], &ambient[1],
						&ambient[2], &ambient[3]) != 4) {
			printf(
					"WARNING: could not parse lighting > ambient. Using defaults.\n");
			ambient[0] = 0.5;
			ambient[1] = 0.5;
			ambient[2] = 0.7;
			ambient[3] = 0.5;
		}
	} else {
		printf("WARNING: lighting block not found. Using defaults.\n");
		doublesided = "true";
		local = "false";
		enabled = "true";
		ambient[0] = 0.5;
		ambient[1] = 0.5;
		ambient[2] = 0.7;
		ambient[3] = 0.5;
	}

	printf("  lighting:\n");
	printf("    doublesided value [true|false]: %s\n", doublesided.c_str());
	printf("    local value [true|false]: %s\n", local.c_str());
	printf("    enabled value [true|false]: %s\n", enabled.c_str());
	printf("    ambient values [RGBA]: %f %f %f %f\n", ambient[0], ambient[1],
			ambient[2], ambient[3]);
}

void XMLParser::parseCameras() {
	camerasElement = anfElement->FirstChildElement("cameras");

}

void XMLParser::parseLights() {

}

void XMLParser::parseTextures() {

}

void XMLParser::parseAppearances() {

}

void XMLParser::parseGraph() {
	graphElement = anfElement->FirstChildElement("graph");

	if (graphElement == NULL)
		printf("ERROR: graph block not found. Exiting.\n");
	else {
		TiXmlElement* node = graphElement->FirstChildElement();

		/*
		 while (node) {
		 printf("Node id '%s' - Descendants:\n", node->Attribute("id"));
		 TiXmlElement *child = node->FirstChildElement();
		 while (child) {
		 if (strcmp(child->Value(), "Node") == 0) {
		 // access node data by searching for its id in the nodes section

		 TiXmlElement* noderef = findChildByAttribute(nodesElement,
		 "id", child->Attribute("id"));

		 if (noderef) {
		 // print id
		 printf("  - Node id: '%s'\n", child->Attribute("id"));

		 // prints some of the data
		 printf("    - Material id: '%s' \n",
		 noderef->FirstChildElement("material")->Attribute(
		 "id"));
		 printf("    - Texture id: '%s' \n",
		 noderef->FirstChildElement("texture")->Attribute(
		 "id"));

		 // repeat for other leaf details
		 } else
		 printf(
		 "  - Node id: '%s': NOT FOUND IN THE NODES SECTION\n",
		 child->Attribute("id"));

		 }
		 if (strcmp(child->Value(), "Leaf") == 0) {
		 // access leaf data by searching for its id in the leaves section
		 TiXmlElement *leaf = findChildByAttribute(leavesElement,
		 "id", child->Attribute("id"));

		 if (leaf) {
		 // it is a leaf and it is present in the leaves section
		 printf("  - Leaf id: '%s' ; type: '%s'\n",
		 child->Attribute("id"),
		 leaf->Attribute("type"));

		 // repeat for other leaf details
		 } else
		 printf(
		 "  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",
		 child->Attribute("id"));
		 }

		 child = child->NextSiblingElement();
		 }
		 node = node->NextSiblingElement();
		 }
		 */
	}
}

XMLParser::~XMLParser() {
	delete (doc);
}

TiXmlElement* XMLParser::findChildByAttribute(TiXmlElement* parent,
		const char* attr, const char* val) {
	TiXmlElement* child = parent->FirstChildElement();

	int found = 0;
	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr), val) == 0)
			found = 1;
		else
			child = child->NextSiblingElement();

	return child;
}
