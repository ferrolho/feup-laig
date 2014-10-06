#include "XMLParser.h"

#include "Point3D.h"
#include "RGBA.h"
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

float getFloat(TiXmlElement* element, string elementString, string attribute,
		float defaultValue) {
	char* temp = NULL;
	temp = (char*) element->Attribute(attribute.c_str());

	float res;
	if (!temp || sscanf(temp, "%f", &res) != 1) {
		printf("WARNING: could not parse %s > %s. Using defaults.\n",
				elementString.c_str(), attribute.c_str());
		res = defaultValue;
	}

	return res;
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

	if (camerasElement) {
		TiXmlElement* element;

		printf("processing cameras:\n");

		// --- initial --- //
		string initial = camerasElement->Attribute("initial");
		printf("  initial: %s\n", initial.c_str());

		element = camerasElement->FirstChildElement("perspective");
		while (element) {
			parsePerspectiveCamera(element);

			element = element->NextSiblingElement("perspective");
		}

		element = camerasElement->FirstChildElement("ortho");
		while (element) {
			parseOrthoCamera(element);

			element = element->NextSiblingElement("ortho");
		}

		/* TODO
		 * ensure the following:
		 *	- lights have different names
		 *	- there are no more than 8 lights
		 *	- the initial camera exists
		 */
	} else {
		printf("WARNING: cameras block not found. Using defaults.\n");

		// TODO add default values here
	}
}

void XMLParser::parsePerspectiveCamera(TiXmlElement* element) {
	string id;
	float near, far, angle;
	Point3D pos, target;

	if (element) {
		char* valString;
		float x, y, z;

		// --- id --- //
		id = element->Attribute("id");

		// --- near --- //
		near = getFloat(element, "perspective", "near", 0.1);

		// --- far --- //
		far = getFloat(element, "perspective", "far", 0.2);

		// --- angle --- //
		angle = getFloat(element, "perspective", "angle", 35.0);

		// --- pos --- //
		valString = NULL;
		valString = (char*) element->Attribute("pos");
		if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
			printf(
					"WARNING: could not parse perspective > pos. Using defaults.\n");
			x = y = z = 0;
		}
		pos = Point3D(x, y, z);

		// --- target --- //
		valString = NULL;
		valString = (char*) element->Attribute("target");
		if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
			printf(
					"WARNING: could not parse perspective > target. Using defaults.\n");
			x = y = z = 1;
		}
		target = Point3D(x, y, z);
	} else {
		printf("WARNING: perspective block not found. Using defaults.\n");
		id = "perspectiveCam";
		near = 0.1;
		far = 0.2;
		angle = 35;
		pos = Point3D();
		target = Point3D(1, 1, 1);
	}

	printf("  perspective:\n");
	printf("    id: %s\n", id.c_str());
	printf("    near: %f\n", near);
	printf("    far: %f\n", far);
	printf("    angle: %f\n", angle);
	printf("    pos: %s\n", pos.toString().c_str());
	printf("    target: %s\n", target.toString().c_str());
}

void XMLParser::parseOrthoCamera(TiXmlElement* element) {
	string id, direction;
	float near, far, left, right, top, bottom;

	if (element) {
		vector<string> candidates;

		// --- id --- //
		id = element->Attribute("id");

		// --- direction --- //
		candidates.push_back("x");
		candidates.push_back("y");
		candidates.push_back("z");
		direction = assignAndValidate(element, "ortho", "direction", candidates,
				candidates[0]);

		// --- near --- //
		near = getFloat(element, "ortho", "near", 0.1);

		// --- far --- //
		far = getFloat(element, "ortho", "far", 0.2);

		// --- left --- //
		left = getFloat(element, "ortho", "left", -1);

		// --- right --- //
		right = getFloat(element, "ortho", "right", 1);

		// --- top --- //
		top = getFloat(element, "ortho", "top", -1);

		// --- bottom --- //
		bottom = getFloat(element, "ortho", "bottom", 1);
	} else {
		printf("WARNING: ortho block not found. Using defaults.\n");
		id = "orthoCam";
		direction = "x";
		near = 0.1;
		far = 0.2;
		left = -1;
		right = 1;
		top = -1;
		bottom = 1;
	}

	printf("  ortho:\n");
	printf("    id: %s\n", id.c_str());
	printf("    direction: %s\n", direction.c_str());
	printf("    near: %f\n", near);
	printf("    far: %f\n", far);
	printf("    left: %f\n", left);
	printf("    right: %f\n", right);
	printf("    top: %f\n", top);
	printf("    bottom: %f\n", bottom);
}

void XMLParser::parseLights() {
	lightsElement = anfElement->FirstChildElement("lights");

	if (lightsElement) {
		printf("processing lights:\n");

		TiXmlElement* element = lightsElement->FirstChildElement("light");

		while (element) {
			parseLight(element);

			element = element->NextSiblingElement("light");
		}
	} else {
		printf("WARNING: lights block not found. Using defaults.\n");

		// TODO add default values here
	}
}

void XMLParser::parseLight(TiXmlElement* element) {
	string id, type, enabled, marker;
	Point3D pos, target;
	float angle, exponent;
	bool isSpot = false;

	if (element) {
		vector<string> candidates;
		char* valString;
		float x, y, z;

		// --- id --- //
		id = element->Attribute("id");

		// --- type --- //
		candidates.push_back("omni");
		candidates.push_back("spot");
		type = assignAndValidate(element, "light", "type", candidates,
				candidates[0]);
		isSpot = type.compare(candidates[1]) == 0;

		// --- enabled --- //
		candidates.clear();
		candidates.push_back("false");
		candidates.push_back("true");
		enabled = assignAndValidate(element, "light", "enabled", candidates,
				candidates[1]);

		// --- marker --- //
		marker = assignAndValidate(element, "light", "marker", candidates,
				candidates[1]);

		// --- pos --- //
		valString = NULL;
		valString = (char*) element->Attribute("pos");
		if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
			printf("WARNING: could not parse light > pos. Using defaults.\n");
			x = y = z = 0;
		}
		pos = Point3D(x, y, z);

		if (isSpot) {
			// --- target --- //
			valString = NULL;
			valString = (char*) element->Attribute("target");
			if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
				printf(
						"WARNING: could not parse light > target. Using defaults.\n");
				x = y = z = 1;
			}
			target = Point3D(x, y, z);

			// --- angle --- //
			angle = getFloat(element, "light", "angle", 30);

			// --- exponent --- //
			exponent = getFloat(element, "light", "exponent", 1);
		}
	} else {
		printf("WARNING: light block not found. Using defaults.\n");
		id = "omniLight";
		type = "omni";
		enabled = "true";
		marker = "true";
		pos = Point3D();

		if (isSpot) {
			target = Point3D(1, 1, 1);
			angle = 30;
			exponent = 1;
		}
	}

	printf("  light:\n");
	printf("    id: %s\n", id.c_str());
	printf("    type: %s\n", type.c_str());
	printf("    enabled: %s\n", enabled.c_str());
	printf("    marker: %s\n", marker.c_str());
	printf("    pos: %s\n", pos.toString().c_str());
	if (isSpot) {
		printf("    target: %s\n", target.toString().c_str());
		printf("    angle: %f\n", angle);
		printf("    exponent: %f\n", exponent);
	}

	parseLightComponents(element);
}

void XMLParser::parseLightComponents(TiXmlElement* element) {
	vector<string> candidates;
	candidates.push_back("ambient");
	candidates.push_back("diffuse");
	candidates.push_back("specular");

	TiXmlElement* component = element->FirstChildElement("component");
	while (component) {
		string type;
		RGBA value;
		char* valString;
		float r, g, b, a;

		// --- type --- //
		type = assignAndValidate(component, "component", "type", candidates,
				candidates[0]);

		// --- value --- //
		valString = NULL;
		valString = (char*) component->Attribute("value");
		if (!valString
				|| sscanf(valString, "%f %f %f %f", &r, &g, &b, &a) != 4) {
			printf(
					"WARNING: could not parse component > value. Using defaults.\n");
			r = g = b = 0;
			a = 1;
		}
		value = RGBA(r, g, b, a);

		printf("    component:\n");
		printf("      type: %s\n", type.c_str());
		printf("      value: %s\n", value.toString().c_str());

		component = component->NextSiblingElement();
	}
}

void XMLParser::parseTextures() {
	texturesElement = anfElement->FirstChildElement("textures");

	if (texturesElement) {
		printf("processing textures:\n");

		TiXmlElement* element = texturesElement->FirstChildElement("texture");

		while (element) {
			parseTexture(element);

			element = element->NextSiblingElement();
		}
	} else {
		printf("WARNING: textures block not found. Using defaults.\n");

		// TODO add default values here
	}
}

void XMLParser::parseTexture(TiXmlElement* element) {
	string id, file;
	float texlength_s, texlength_t;

	if (element) {
		// --- id --- //
		id = element->Attribute("id");

		// --- file --- //
		file = element->Attribute("file");

		// --- texlength_s --- //
		texlength_s = getFloat(element, "texture", "texlength_s", 0.5);

		// --- texlength_t --- //
		texlength_t = getFloat(element, "texture", "texlength_t", 0.5);
	}

	printf("  texture:\n");
	printf("    id: %s\n", id.c_str());
	printf("    file: %s\n", file.c_str());
	printf("    texlength_s: %f\n", texlength_s);
	printf("    texlength_t: %f\n", texlength_t);
}

void XMLParser::parseAppearances() {
	appearencesElement = anfElement->FirstChildElement("appearances");

	if (appearencesElement) {
		printf("processing appearances:\n");

		TiXmlElement* element = appearencesElement->FirstChildElement(
				"appearance");

		while (element) {
			parseAppearance(element);

			element = element->NextSiblingElement("appearance");
		}
	} else {
		printf("WARNING: appearances block not found. Using defaults.\n");

		// TODO add default values here
	}
}

void XMLParser::parseAppearance(TiXmlElement* element) {
	string id, textureref;
	float shininess;

	if (element) {
		// --- id --- //
		id = element->Attribute("id");

		// --- shininess --- //
		shininess = getFloat(element, "appearance", "shininess", 1.0);

		// --- textureref --- //
		textureref = element->Attribute("textureref");
	} else {
		printf("WARNING: appearance block not found. Using defaults.\n");
		id = "defaultAppearance";
		shininess = 1.0;
		textureref = "";
	}

	printf("  appearance:\n");
	printf("    id: %s\n", id.c_str());
	printf("    shininess: %f\n", shininess);
	printf("    textureref: %s\n", textureref.c_str());

	parseAppearanceComponents(element);
}

void XMLParser::parseAppearanceComponents(TiXmlElement* element) {
	vector<string> candidates;
	candidates.push_back("ambient");
	candidates.push_back("diffuse");
	candidates.push_back("specular");

	TiXmlElement* component = element->FirstChildElement("component");
	while (component) {
		string type;
		RGBA value;
		char* valString;
		float r, g, b, a;

		// --- type --- //
		type = assignAndValidate(component, "component", "type", candidates,
				candidates[0]);

		// --- value --- //
		valString = NULL;
		valString = (char*) component->Attribute("value");
		if (!valString
				|| sscanf(valString, "%f %f %f %f", &r, &g, &b, &a) != 4) {
			printf(
					"WARNING: could not parse component > value. Using defaults.\n");
			r = g = b = 0;
			a = 1;
		}
		value = RGBA(r, g, b, a);

		printf("    component:\n");
		printf("      type: %s\n", type.c_str());
		printf("      value: %s\n", value.toString().c_str());

		component = component->NextSiblingElement();
	}
}

void XMLParser::parseGraph() {
	graphElement = anfElement->FirstChildElement("graph");

	if (graphElement) {
		printf("processing graph:\n");

		// --- rootid --- //
		string rootid = graphElement->Attribute("rootid");
		printf("  rootid: %s\n", rootid.c_str());

		TiXmlElement* element = graphElement->FirstChildElement("node");

		if (element) {
			while (element) {
				parseNode(element);

				element = element->NextSiblingElement("node");
			}
		} else {
			printf("ERROR: node block not found. Exiting.\n");
			exit(1);
		}
	} else {
		printf("ERROR: graph block not found. Exiting.\n");
		exit(1);
	}
}

void XMLParser::parseNode(TiXmlElement* element) {
	string id;
	bool hasPrimitives = false;
	bool hasDescendants = false;

	// --- node ID --- //
	id = element->Attribute("id");
	printf("  processing node:\n");
	printf("    id: %s\n", id.c_str());

	// --- transforms --- //
	TiXmlElement* transformsElement = element->FirstChildElement("transforms");
	if (transformsElement) {
		parseTransforms(transformsElement);
	} else {
		printf("ERROR: transforms block not found! Exiting.\n");
		exit(1);
	}

	// --- appearanceref --- //
	parseAppearanceRef(element);

	// --- primitives --- //
	TiXmlElement* primitivesElement = element->FirstChildElement("primitives");
	if (primitivesElement) {
		hasPrimitives = true;
		parsePrimitives(primitivesElement);
	}

	// --- descendants --- //
	TiXmlElement* descendantsElement = element->FirstChildElement(
			"descendants");
	if (descendantsElement) {
		hasDescendants = true;
		parseDescendants(descendantsElement);
	}

	if (!hasPrimitives && !hasDescendants) {
		printf(
				"ERROR: neither primitives nor descendants block found! Exiting.\n");
		exit(1);
	}
}

void XMLParser::parseTransforms(TiXmlElement* element) {
	printf("    processing transforms:\n");

	TiXmlElement* transformElement = element->FirstChildElement("transform");

	while (transformElement) {
		parseTransform(transformElement);

		transformElement = transformElement->NextSiblingElement("transform");
	}
}

void XMLParser::parseTransform(TiXmlElement* element) {
	printf("      transform:\n");

	string type;

	vector<string> candidates;
	candidates.push_back("translate");
	candidates.push_back("rotate");
	candidates.push_back("scale");

	// --- type --- //
	type = element->Attribute("type");
	if (type.compare(candidates[0]) == 0) {
		printf("        type: %s\n", type.c_str());
		parseTranslate(element);
	} else if (type.compare(candidates[1]) == 0) {
		printf("        type: %s\n", type.c_str());
		parseRotate(element);
	} else if (type.compare(candidates[2]) == 0) {
		printf("        type: %s\n", type.c_str());
		parseScale(element);
	} else
		printf("WARNING: invalid transform > type. Skiping transform.\n");
}

void XMLParser::parseTranslate(TiXmlElement* element) {
	Point3D to;
	char* valString = NULL;
	float x, y, z;

	// --- to --- //
	valString = (char*) element->Attribute("to");
	if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
		printf("WARNING: could not parse transform > to. Using defaults.\n");
		x = y = z = 0;
	}
	to = Point3D(x, y, z);

	printf("        to: %s\n", to.toString().c_str());
}

void XMLParser::parseRotate(TiXmlElement* element) {
	string axis;
	float angle;
	vector<string> candidates;

	// --- axis --- //
	candidates.push_back("x");
	candidates.push_back("y");
	candidates.push_back("z");
	axis = assignAndValidate(element, "transform", "axis", candidates,
			candidates[0]);

	// --- angle --- //
	angle = getFloat(element, "transform", "angle", 0);

	printf("        axis: %s\n", axis.c_str());
	printf("        angle: %f\n", angle);
}

void XMLParser::parseScale(TiXmlElement* element) {
	Point3D factor;
	char* valString = NULL;
	float x, y, z;

	// --- factor --- //
	valString = (char*) element->Attribute("factor");
	if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
		printf(
				"WARNING: could not parse transform > values. Using defaults.\n");
		x = y = z = 1;
	}
	factor = Point3D(x, y, z);

	printf("        factor: %s\n", factor.toString().c_str());
}

void XMLParser::parseAppearanceRef(TiXmlElement* element) {
	printf("    processing appearanceref:\n");

	// --- id --- //
	string id = element->Attribute("id");
	if (id.empty()) {
		printf("WARNING: empty node > appearanceref > id. Using default.\n");
		id = "inherit";
	}

	printf("      id: %s\n", id.c_str());
}

void XMLParser::parsePrimitives(TiXmlElement* element) {
	printf("    processing primitives:\n");

}

void XMLParser::parseRectangle(TiXmlElement* element) {

}

void XMLParser::parseTriangle(TiXmlElement* element) {

}

void XMLParser::parseCylinder(TiXmlElement* element) {

}

void XMLParser::parseSphere(TiXmlElement* element) {

}

void XMLParser::parseTorus(TiXmlElement* element) {

}

void XMLParser::parseDescendants(TiXmlElement* element) {
	printf("    processing descendants:\n");
}

void XMLParser::parseNodeRef(TiXmlElement* element) {

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
