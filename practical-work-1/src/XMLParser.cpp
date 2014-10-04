#include "XMLParser.h"

#include <string>

using namespace std;

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

void XMLParser::parseGlobals() {
	globalsElement = anfElement->FirstChildElement("globals");

	if (globalsElement == NULL) {
		printf("WARNING: globals block not found. Using defaults.\n");
		// TODO add default values here

	} else {
		printf("processing globals:\n");

		// ----- drawing ----- //
		string mode, shading;
		float background[4];

		TiXmlElement* drawingElement = globalsElement->FirstChildElement(
				"drawing");
		if (drawingElement) {
			// --- mode --- //
			mode = drawingElement->Attribute("mode");
			if (mode.compare("fill") != 0 && mode.compare("line") != 0
					&& mode.compare("point") != 0) {
				printf("WARNING: invalid drawing mode. Using default: fill.\n");
				mode = "fill";
			}

			// --- shading --- //
			shading = drawingElement->Attribute("shading");
			if (shading.compare("flat") != 0
					&& shading.compare("gouraud") != 0) {
				printf(
						"WARNING: invalid drawing shading. Using default: flat.\n");
				shading = "flat";
			}

			// --- background --- //
			char* valString = NULL;
			valString = (char*) drawingElement->Attribute("background");
			if (!valString
					|| sscanf(valString, "%f %f %f %f", &background[0],
							&background[1], &background[2], &background[3])
							!= 4) {
				printf(
						"WARNING: could not parse drawing background. Using defaults.\n");
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

		// ----- culling ----- //
		TiXmlElement* cullingElement = globalsElement->FirstChildElement(
				"culling");
		if (cullingElement) {
			printf("  culling:\n");

			string face = cullingElement->Attribute("face");
			printf("    face value [none|back|front|both]: %s\n", face.c_str());

			string order = cullingElement->Attribute("order");
			printf("    order value [ccw|cw]: %s\n", order.c_str());
		} else
			printf("culling not found\n");

		// ----- lighting ----- //
		float ambient[4];

		TiXmlElement* lightingElement = globalsElement->FirstChildElement(
				"lighting");
		if (lightingElement) {
			printf("  lighting:\n");

			string doublesided = lightingElement->Attribute("doublesided");
			printf("    doublesided value [true|false]: %s\n",
					doublesided.c_str());

			string local = lightingElement->Attribute("local");
			printf("    local value [true|false]: %s\n", local.c_str());

			string enabled = lightingElement->Attribute("enabled");
			printf("    enabled value [true|false]: %s\n", enabled.c_str());

			char* valString = NULL;
			valString = (char*) lightingElement->Attribute("ambient");
			if (valString
					&& sscanf(valString, "%f %f %f %f", &ambient[0],
							&ambient[1], &ambient[2], &ambient[3]) == 4) {
				printf("    ambient values [RGBA]: %f %f %f %f\n", ambient[0],
						ambient[1], ambient[2], ambient[3]);
			} else
				printf("Error parsing lighting");
		} else
			printf("lighting not found\n");
	}
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
