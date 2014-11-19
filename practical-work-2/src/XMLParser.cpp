#include "XMLParser.h"

#include "CGFapplication.h"
#include "Point3D.h"
#include "RGBA.h"
#include "Utilities.h"

XMLParser::XMLParser(const char* filename, Globals& globals, Cameras& cameras,
		Lights& lights, SceneGraph* graph) :
		rootid("") {
	loadXMLFile(filename);

	printf("Starting to parse ANF.\n");
	loadAnfElement();
	globals = parseGlobals();
	cameras = parseCameras();
	lights = parseLights();
	parseTextures();
	parseAppearances();
	parseGraph(graph);
	printf("ANF successfully parsed.\n");
}

XMLParser::~XMLParser() {
	delete (doc);
}

void XMLParser::loadXMLFile(const char* filename) {
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

string XMLParser::assignAndValidate(TiXmlElement* element,
		const string& elementStr, const string& attribute,
		const vector<string>& candidates, const string& defaultValue) {
	if (!element->Attribute(attribute.c_str()))
		return defaultValue;

	// read attribute from xml
	string str = element->Attribute(attribute.c_str());

	// look for a match between the xml attribute and any element of the list
	bool matchFound = false;
	for (vector<string>::const_iterator it = candidates.begin();
			it != candidates.end(); it++) {
		if (str.compare(*it) == 0) {
			matchFound = true;
			break;
		}
	}

	// if no match found, assign the default value
	if (!matchFound) {
		printf("WARNING: invalid %s > %s. Using default: %s.\n",
				elementStr.c_str(), attribute.c_str(), defaultValue.c_str());
		printf("\nPress any key to continue...\n");
		getchar();
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
		printf("\nPress any key to continue...\n");
		getchar();
		res = defaultValue;
	}

	return res;
}

int getInt(TiXmlElement* element, string elementString, string attribute,
		int defaultValue) {
	char* temp = NULL;
	temp = (char*) element->Attribute(attribute.c_str());

	int res;
	if (!temp || sscanf(temp, "%d", &res) != 1) {
		printf("WARNING: could not parse %s > %s. Using defaults.\n",
				elementString.c_str(), attribute.c_str());
		printf("\nPress any key to continue...\n");
		getchar();
		res = defaultValue;
	}

	return res;
}

Globals* XMLParser::parseGlobals() {
	Globals* globals = new Globals();

	globalsElement = anfElement->FirstChildElement("globals");

	if (globalsElement) {
		printf("processing globals:\n");

		globals->setDrawing(parseGlobalsDrawing());
		globals->setCulling(parseGlobalsCulling());
		globals->setLighting(parseGlobalsLighting());
	} else {
		printf("WARNING: globals block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();

		// TODO add default values here
	}

	return globals;
}

Drawing* XMLParser::parseGlobalsDrawing() {
	string mode, shading;
	RGBA* background;

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
		float r, g, b, a;
		char* valString = NULL;
		valString = (char*) drawingElement->Attribute("background");
		if (!valString
				|| sscanf(valString, "%f %f %f %f", &r, &g, &b, &a) != 4) {
			printf(
					"WARNING: could not parse drawing > background. Using defaults.\n");
			printf("\nPress any key to continue...\n");
			getchar();
			background = new RGBA();
		}
		background = new RGBA(r, g, b, a);
	} else {
		printf("WARNING: drawing block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		mode = "fill";
		shading = "flat";
		background = new RGBA();
	}

	printf("  drawing:\n");
	printf("    mode value [fill|line|point]: %s\n", mode.c_str());
	printf("    shading value [flat|gouraud]: %s\n", shading.c_str());
	printf("    background values [RGBA]: %s\n",
			background->toString().c_str());

	return new Drawing(mode, shading, background);
}

Culling* XMLParser::parseGlobalsCulling() {
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
		printf("\nPress any key to continue...\n");
		getchar();
		face = "back";
		order = "ccw";
	}

	printf("  culling:\n");
	printf("    face value [none|back|front|both]: %s\n", face.c_str());
	printf("    order value [ccw|cw]: %s\n", order.c_str());

	return new Culling(face, order);
}

Lighting* XMLParser::parseGlobalsLighting() {
	string doublesided, local, enabled;
	RGBA* ambient;

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
		float r, g, b, a;
		char* valString = NULL;
		valString = (char*) lightingElement->Attribute("ambient");
		if (!valString
				|| sscanf(valString, "%f %f %f %f", &r, &g, &b, &a) != 4) {
			printf(
					"WARNING: could not parse lighting > ambient. Using defaults.\n");
			printf("\nPress any key to continue...\n");
			getchar();
			ambient = new RGBA(0.2, 0.2, 0.2, 1);
		}
		ambient = new RGBA(r, g, b, a);
	} else {
		printf("WARNING: lighting block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		doublesided = "true";
		local = "false";
		enabled = "true";
		ambient = new RGBA(0.2, 0.2, 0.2, 1);
	}

	printf("  lighting:\n");
	printf("    doublesided value [true|false]: %s\n", doublesided.c_str());
	printf("    local value [true|false]: %s\n", local.c_str());
	printf("    enabled value [true|false]: %s\n", enabled.c_str());
	printf("    ambient values [RGBA]: %s\n", ambient->toString().c_str());

	return new Lighting(doublesided, local, enabled, ambient);
}

Cameras* XMLParser::parseCameras() {
	Cameras* cameras = new Cameras();

	camerasElement = anfElement->FirstChildElement("cameras");

	if (camerasElement) {
		TiXmlElement* element;

		printf("processing cameras:\n");

		// --- initial --- //
		cameras->setActiveCameraID(camerasElement->Attribute("initial"));
		printf("  initial: %s\n", cameras->getActiveCameraID().c_str());

		element = camerasElement->FirstChildElement("perspective");
		while (element) {
			cameras->add(parsePerspectiveCamera(element));

			element = element->NextSiblingElement("perspective");
		}

		element = camerasElement->FirstChildElement("ortho");
		while (element) {
			cameras->add(parseOrthoCamera(element));

			element = element->NextSiblingElement("ortho");
		}

		// TODO our free camera
		/*
		 FreeCamera* camera = new FreeCamera();
		 cameras->add(camera);
		 cameras->setActiveCamera("");*/
	} else {
		printf("WARNING: cameras block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();

		// TODO add default values here
	}

	return cameras;
}

Perspective* XMLParser::parsePerspectiveCamera(TiXmlElement* element) {
	string id;
	float near, far, angle;
	Point3D *pos, *target;

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
			printf("\nPress any key to continue...\n");
			getchar();
			x = y = z = 0;
		}
		pos = new Point3D(x, y, z);

		// --- target --- //
		valString = NULL;
		valString = (char*) element->Attribute("target");
		if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
			printf(
					"WARNING: could not parse perspective > target. Using defaults.\n");
			printf("\nPress any key to continue...\n");
			getchar();
			x = y = z = 1;
		}
		target = new Point3D(x, y, z);
	} else {
		printf("WARNING: perspective block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		id = "perspectiveCam";
		near = 0.1;
		far = 0.2;
		angle = 35;
		pos = new Point3D();
		target = new Point3D(1, 1, 1);
	}

	printf("  perspective:\n");
	printf("    id: %s\n", id.c_str());
	printf("    near: %f\n", near);
	printf("    far: %f\n", far);
	printf("    angle: %f\n", angle);
	printf("    pos: %s\n", pos->toString().c_str());
	printf("    target: %s\n", target->toString().c_str());

	return new Perspective(id, near, far, angle, pos, target);
}

Ortho* XMLParser::parseOrthoCamera(TiXmlElement* element) {
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
		printf("\nPress any key to continue...\n");
		getchar();
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

	return new Ortho(id, near, far, direction[0], left, right, top, bottom);
}

Lights* XMLParser::parseLights() {
	Lights* lights = new Lights();

	lightsElement = anfElement->FirstChildElement("lights");

	if (lightsElement) {
		printf("processing lights:\n");

		TiXmlElement* element = lightsElement->FirstChildElement("light");

		while (element && Light::getNextLightID() <= 8) {
			lights->add(parseLight(element));

			element = element->NextSiblingElement("light");

			/* TODO
			 * ensure the following:
			 *	- lights have different names
			 *	- there are no more than 8 lights
			 *	- the initial camera exists
			 */
		}
	} else {
		printf("WARNING: lights block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();

		// TODO add default values here
	}

	return lights;
}

Light* XMLParser::parseLight(TiXmlElement* element) {
	string id, type, enabled, marker;
	Point3D pos, target;
	float angle = 0, exponent = 1;
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
			printf("\nPress any key to continue...\n");
			getchar();
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
				printf("\nPress any key to continue...\n");
				getchar();
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
		printf("\nPress any key to continue...\n");
		getchar();
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

	target -= pos;
	target = normalizeVector(target);

	Components* components = parseLightComponents(element);

	if (isSpot)
		return new SpotLight(id, enabled, marker, pos, target, angle, exponent,
				components);
	else
		return new Light(id, enabled, marker, pos, components);
}

Components* XMLParser::parseLightComponents(TiXmlElement* element) {
	vector<RGBA*> components;

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
			printf("\nPress any key to continue...\n");
			getchar();
			r = g = b = 0;
			a = 1;
		}
		value = RGBA(r, g, b, a);

		printf("    component:\n");
		printf("      type: %s\n", type.c_str());
		printf("      value: %s\n", value.toString().c_str());

		components.push_back(new RGBA(r, g, b, a));

		component = component->NextSiblingElement();
	}

	return new Components(components[0], components[1], components[2]);
}

void XMLParser::parseTextures() {
	texturesElement = anfElement->FirstChildElement("textures");

	if (texturesElement) {
		printf("processing textures:\n");

		TiXmlElement* element = texturesElement->FirstChildElement("texture");

		while (element) {
			Texture* texture = parseTexture(element);

			if (texture)
				textures[texture->getId()] = texture;

			element = element->NextSiblingElement();
		}
	} else {
		printf("WARNING: textures block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();

		// TODO add default values here
	}
}

Texture* XMLParser::parseTexture(TiXmlElement* element) {
	string id, file;
	float texlength_s = 1, texlength_t = 1;

	if (element) {
		// --- id --- //
		id = element->Attribute("id");

		// --- file --- //
		file = element->Attribute("file");

		if (!fileExists(file)) {
			printf("ERROR: texture resource not found.\n");
			printf("\nPress any key to continue...\n");
			getchar();
			return NULL;
		}

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

	return new Texture(id, file, texlength_s, texlength_t);
}

void XMLParser::parseAppearances() {
	appearencesElement = anfElement->FirstChildElement("appearances");

	if (appearencesElement) {
		printf("processing appearances:\n");

		TiXmlElement* element = appearencesElement->FirstChildElement(
				"appearance");

		while (element) {
			Appearance* appearance = parseAppearance(element);
			appearances[appearance->getId()] = appearance;

			element = element->NextSiblingElement("appearance");
		}
	} else {
		printf("WARNING: appearances block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();

		// TODO add default values here
	}
}

Appearance* XMLParser::parseAppearance(TiXmlElement* element) {
	string id, textureref;
	float shininess;

	if (element) {
		// --- id --- //
		id = element->Attribute("id");

		// --- shininess --- //
		shininess = getFloat(element, "appearance", "shininess", 1.0);

		// --- textureref --- //
		if (element->Attribute("textureref"))
			textureref = element->Attribute("textureref");
	} else {
		printf("WARNING: appearance block not found. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		id = "defaultAppearance";
		shininess = 1.0;
	}

	printf("  appearance:\n");
	printf("    id: %s\n", id.c_str());
	printf("    shininess: %f\n", shininess);
	printf("    textureref: %s\n", textureref.c_str());

	Components* components = parseAppearanceComponents(element);
	return new Appearance(id, shininess, textures[textureref], components);
}

Components* XMLParser::parseAppearanceComponents(TiXmlElement* element) {
	vector<RGBA*> components;

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
			printf("\nPress any key to continue...\n");
			getchar();
			r = g = b = 0;
			a = 1;
		}
		value = RGBA(r, g, b, a);

		printf("    component:\n");
		printf("      type: %s\n", type.c_str());
		printf("      value: %s\n", value.toString().c_str());

		components.push_back(new RGBA(r, g, b, a));

		component = component->NextSiblingElement();
	}

	return new Components(components[0], components[1], components[2]);
}

void XMLParser::parseGraph(SceneGraph* graph) {
	graphElement = anfElement->FirstChildElement("graph");

	if (graphElement) {
		printf("processing graph:\n");

		// --- rootid --- //
		rootid = graphElement->Attribute("rootid");
		printf("  rootid: %s\n", rootid.c_str());

		TiXmlElement* element = graphElement->FirstChildElement("node");

		if (element) {
			while (element) {
				parseNode(element);

				element = element->NextSiblingElement("node");
			}
		} else {
			printf("ERROR: node block not found. Exiting.\n");
			printf("\nPress any key to continue...\n");
			getchar();
			exit(1);
		}
	} else {
		printf("ERROR: graph block not found. Exiting.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		exit(1);
	}

	Node* root = nodes[rootid];
	graph->setRoot(root);
	parseNodeDescendants(root, root->getAppearance(), root->isDisplayList());
}

void XMLParser::parseNode(TiXmlElement* element) {
	string id, displaylist;
	Appearance* appearance;
	vector<string> descendantsIds;
	vector<Primitive*> primitives;
	Matrix transforms;

	bool hasPrimitives = false;
	bool hasDescendants = false;

	// --- node ID --- //
	id = element->Attribute("id");
	printf("  processing node:\n");
	printf("    id: %s\n", id.c_str());

	// --- display list --- //
	vector<string> candidates;
	candidates.push_back("false");
	candidates.push_back("true");
	displaylist = assignAndValidate(element, "node", "displaylist", candidates,
			candidates[0]);
	printf("    displaylist: %s\n", displaylist.c_str());

	// --- transforms --- //
	TiXmlElement* transformsElement = element->FirstChildElement("transforms");
	if (transformsElement) {
		transforms = parseTransforms(transformsElement);
	} else {
		printf("ERROR: transforms block not found! Exiting.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		exit(1);
	}

	// --- appearanceref --- //
	TiXmlElement* appearenceRefElement = element->FirstChildElement(
			"appearanceref");
	if (appearenceRefElement)
		appearance = parseAppearanceRef(appearenceRefElement);
	else {
		printf("ERROR: appearanceref block not found! Exiting.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		exit(1);
	}

	// --- primitives --- //
	TiXmlElement* primitivesElement = element->FirstChildElement("primitives");
	if (primitivesElement) {
		hasPrimitives = true;

		if (appearance)
			primitives = parsePrimitives(primitivesElement,
					appearance->getTexture());
		else
			primitives = parsePrimitives(primitivesElement);
	}

	// --- descendants --- //
	TiXmlElement* descendantsElement = element->FirstChildElement(
			"descendants");
	if (descendantsElement) {
		hasDescendants = true;
		descendantsIds = parseDescendants(descendantsElement);
	}

	if (!hasPrimitives && !hasDescendants) {
		printf(
				"ERROR: neither primitives nor descendants block found! Exiting.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		exit(1);
	}

	nodes[id] = new Node(id, displaylist, appearance, descendantsIds,
			primitives, transforms);
}

Matrix XMLParser::parseTransforms(TiXmlElement* element) {
	vector<Transform*> transforms;

	printf("    processing transforms:\n");

	TiXmlElement* transformElement = element->FirstChildElement("transform");

	while (transformElement) {
		transforms.push_back(parseTransform(transformElement));

		transformElement = transformElement->NextSiblingElement("transform");
	}

	Matrix mp;
	glPushMatrix();
	glLoadIdentity();
	for (unsigned int i = 0; i < transforms.size(); i++)
		transforms[i]->apply();
	glGetFloatv(GL_MODELVIEW_MATRIX, &mp.matrix[0]);
	glPopMatrix();

	return mp;
}

Transform* XMLParser::parseTransform(TiXmlElement* element) {
	printf("      transform:\n");

	string type;

	vector<string> candidates;
	candidates.push_back("translate");
	candidates.push_back("rotate");
	candidates.push_back("scale");

	// --- type --- //
	type = element->Attribute("type");
	if (type.compare(candidates[0]) == 0) {
		printf("        type [translate|rotate|scale]: %s\n", type.c_str());
		return parseTranslate(element);
	} else if (type.compare(candidates[1]) == 0) {
		printf("        type [translate|rotate|scale]: %s\n", type.c_str());
		return parseRotate(element);
	} else if (type.compare(candidates[2]) == 0) {
		printf("        type [translate|rotate|scale]: %s\n", type.c_str());
		return parseScale(element);
	} else
		printf("WARNING: invalid transform > type. Skiping transform.\n");
	printf("\nPress any key to continue...\n");
	getchar();

	return NULL;
}

Translation* XMLParser::parseTranslate(TiXmlElement* element) {
	Point3D to;
	char* valString = NULL;
	float x, y, z;

	// --- to --- //
	valString = (char*) element->Attribute("to");
	if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
		printf("WARNING: could not parse transform > to. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		x = y = z = 0;
	}
	to = Point3D(x, y, z);

	printf("        to: %s\n", to.toString().c_str());

	return new Translation(to);
}

Rotation* XMLParser::parseRotate(TiXmlElement* element) {
	string axis;
	float angle;
	vector<string> candidates;

	// --- axis --- //
	candidates.push_back("x");
	candidates.push_back("y");
	candidates.push_back("z");
	candidates.push_back("X");
	candidates.push_back("Y");
	candidates.push_back("Z");
	axis = assignAndValidate(element, "transform", "axis", candidates,
			candidates[0]);

	// --- angle --- //
	angle = getFloat(element, "transform", "angle", 0);

	printf("        axis: %s\n", axis.c_str());
	printf("        angle: %f\n", angle);

	return new Rotation(axis, angle);
}

Scaling* XMLParser::parseScale(TiXmlElement* element) {
	Point3D factor;
	char* valString = NULL;
	float x, y, z;

	// --- factor --- //
	valString = (char*) element->Attribute("factor");
	if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
		printf(
				"WARNING: could not parse transform > values. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		x = y = z = 1;
	}
	factor = Point3D(x, y, z);

	printf("        factor: %s\n", factor.toString().c_str());

	return new Scaling(factor);
}

Appearance* XMLParser::parseAppearanceRef(TiXmlElement* element) {
	// --- id --- //
	string id = element->Attribute("id");
	if (id.empty()) {
		printf("WARNING: empty node > appearanceref > id. Using default.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		id = "inherit";
	}

	printf("    processing appearanceref:\n");
	printf("      id: %s\n", id.c_str());

	return id.compare("inherit") == 0 ? NULL : appearances[id];
}

const vector<Primitive*> XMLParser::parsePrimitives(TiXmlElement* element,
		Texture* texture) {
	vector<Primitive*> primitives;

	printf("    processing primitives:\n");

	vector<string> candidates;
	candidates.push_back("rectangle");
	candidates.push_back("triangle");
	candidates.push_back("cylinder");
	candidates.push_back("sphere");
	candidates.push_back("torus");
	candidates.push_back("plane");
	candidates.push_back("patch");

	TiXmlElement* primitive = element->FirstChildElement();

	while (primitive) {
		if (((string) primitive->Value()).compare(candidates[0]) == 0)
			primitives.push_back(parseRectangle(primitive, texture));
		else if (((string) primitive->Value()).compare(candidates[1]) == 0)
			primitives.push_back(parseTriangle(primitive, texture));
		else if (((string) primitive->Value()).compare(candidates[2]) == 0)
			primitives.push_back(parseCylinder(primitive));
		else if (((string) primitive->Value()).compare(candidates[3]) == 0)
			primitives.push_back(parseSphere(primitive));
		else if (((string) primitive->Value()).compare(candidates[4]) == 0)
			primitives.push_back(parseTorus(primitive));
		else if (((string) primitive->Value()).compare(candidates[5]) == 0)
			primitives.push_back(parsePlane(primitive, texture));
		else if (((string) primitive->Value()).compare(candidates[6]) == 0)
			primitives.push_back(parsePatch(primitive, texture));
		else {
			printf("WARNING: invalid primitive tag. Skiping primitive.\n");
			printf("\nPress any key to continue...\n");
			getchar();
		}

		primitive = primitive->NextSiblingElement();
	}

	return primitives;
}

Rectangle* XMLParser::parseRectangle(TiXmlElement* primitive,
		Texture* texture) {
	Point3D xy1, xy2;
	char* valString;
	float x, y;

	// --- xy1 --- //
	valString = NULL;
	valString = (char*) primitive->Attribute("xy1");
	if (!valString || sscanf(valString, "%f %f", &x, &y) != 2) {
		printf("WARNING: could not parse rectangle > xy1. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		x = y = 0;
	}
	xy1 = Point3D(x, y, 0);

	// --- xy2 --- //
	valString = NULL;
	valString = (char*) primitive->Attribute("xy2");
	if (!valString || sscanf(valString, "%f %f", &x, &y) != 2) {
		printf("WARNING: could not parse rectangle > xy2. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		x = y = 0;
	}
	xy2 = Point3D(x, y, 0);

	printf("      rectangle:\n");
	printf("        xy1: %s\n", xy1.toString().c_str());
	printf("        xy2: %s\n", xy2.toString().c_str());

	return new Rectangle(xy1, xy2, texture);
}

Triangle* XMLParser::parseTriangle(TiXmlElement* primitive, Texture* texture) {
	Point3D xyz1, xyz2, xyz3;
	char* valString;
	float x, y, z;

	// --- xyz1 --- //
	valString = NULL;
	valString = (char*) primitive->Attribute("xyz1");
	if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
		printf("WARNING: could not parse triangle > xyz1. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		x = y = z = 0;
	}
	xyz1 = Point3D(x, y, z);

	// --- xyz2 --- //
	valString = NULL;
	valString = (char*) primitive->Attribute("xyz2");
	if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
		printf("WARNING: could not parse triangle > xyz2. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		x = y = z = 0;
	}
	xyz2 = Point3D(x, y, z);

	// --- xyz3 --- //
	valString = NULL;
	valString = (char*) primitive->Attribute("xyz3");
	if (!valString || sscanf(valString, "%f %f %f", &x, &y, &z) != 3) {
		printf("WARNING: could not parse triangle > xyz3. Using defaults.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		x = y = z = 0;
	}
	xyz3 = Point3D(x, y, z);

	printf("      triangle:\n");
	printf("        xyz1: %s\n", xyz1.toString().c_str());
	printf("        xyz2: %s\n", xyz2.toString().c_str());
	printf("        xyz3: %s\n", xyz3.toString().c_str());

	return new Triangle(xyz1, xyz2, xyz3, texture);
}

Cylinder* XMLParser::parseCylinder(TiXmlElement* primitive) {
	float base, top, height;
	int slices, stacks;

	// --- base --- //
	base = getFloat(primitive, primitive->Value(), "base", 1);

	// --- top --- //
	top = getFloat(primitive, primitive->Value(), "top", 1);

	// --- height --- //
	height = getFloat(primitive, primitive->Value(), "height", 1);

	// --- slices --- //
	slices = getInt(primitive, primitive->Value(), "slices", 8);

	// --- stacks --- //
	stacks = getInt(primitive, primitive->Value(), "stacks", 4);

	printf("      cylinder:\n");
	printf("        base: %f\n", base);
	printf("        top: %f\n", top);
	printf("        height: %f\n", height);
	printf("        slices: %d\n", slices);
	printf("        stacks: %d\n", stacks);

	return new Cylinder(base, top, height, slices, stacks);
}

Sphere* XMLParser::parseSphere(TiXmlElement* primitive) {
	float radius;
	int slices, stacks;

	// --- radius --- //
	radius = getFloat(primitive, primitive->Value(), "radius", 1);

	// --- slices --- //
	slices = getInt(primitive, primitive->Value(), "slices", 8);

	// --- stacks --- //
	stacks = getInt(primitive, primitive->Value(), "stacks", 8);

	printf("      sphere:\n");
	printf("        radius: %f\n", radius);
	printf("        slices: %d\n", slices);
	printf("        stacks: %d\n", stacks);

	return new Sphere(radius, slices, stacks);
}

Torus* XMLParser::parseTorus(TiXmlElement* primitive) {
	float inner, outer;
	unsigned int slices, loops;

	// --- inner --- //
	inner = getFloat(primitive, primitive->Value(), "inner", 1);

	// --- outer --- //
	outer = getFloat(primitive, primitive->Value(), "outer", 3);

	// --- slices --- //
	slices = getInt(primitive, primitive->Value(), "slices", 8);

	// --- stacks --- //
	loops = getInt(primitive, primitive->Value(), "loops", 8);

	printf("      torus:\n");
	printf("        inner: %f\n", inner);
	printf("        outer: %f\n", outer);
	printf("        slices: %d\n", slices);
	printf("        loops: %d\n", loops);

	return new Torus(inner, outer, slices, loops);
}

Plane* XMLParser::parsePlane(TiXmlElement* primitive, Texture* texture) {
	// --- parts --- //
	unsigned int parts = getInt(primitive, primitive->Value(), "parts", 10);

	printf("      plane:\n");
	printf("        parts: %d\n", parts);

	return new Plane(parts, texture);
}

Patch* XMLParser::parsePatch(TiXmlElement* primitive, Texture* texture) {
	// --- order --- //
	int order = getInt(primitive, primitive->Value(), "order", 10);

	// --- partsU --- //
	int partsU = getInt(primitive, primitive->Value(), "partsU", 10);

	// --- partsV --- //
	int partsV = getInt(primitive, primitive->Value(), "partsV", 10);

	// --- compute --- //
	string compute = primitive->Attribute("compute");
	if (compute.empty()) {
		printf("WARNING: empty node > patch > compute. Using default.\n");
		printf("\nPress any key to continue...\n");
		getchar();
		compute = "fill";
	}

	// --- control points --- //
	int numPoints = (order + 1) * (order + 1);
	float* controlPoints = (float*) malloc(numPoints * 3 * sizeof(float));

	TiXmlElement* controlpoint = primitive->FirstChildElement("controlpoint");

	int i;
	for (i = 0; i < numPoints; i++) {
		float x = 0, y = 0, z = 0;

		if (controlpoint) {
			x = getInt(controlpoint, controlpoint->Value(), "x", 10);
			y = getInt(controlpoint, controlpoint->Value(), "y", 10);
			z = getInt(controlpoint, controlpoint->Value(), "z", 10);
		} else {
			printf("WARNING: missing patch > controlpoint. Using defaults.\n");
			printf("\nPress any key to continue...\n");
			getchar();
		}

		int i3 = i * 3;
		controlPoints[i3 + 0] = x;
		controlPoints[i3 + 1] = y;
		controlPoints[i3 + 2] = z;

		controlpoint = controlpoint->NextSiblingElement();
	}

	printf("      patch:\n");
	printf("        order: %d\n", order);
	printf("        partsU: %d\n", partsU);
	printf("        partsV: %d\n", partsV);
	printf("        compute: %s\n", compute.c_str());
	printf("        control points:\n");

	for (i = 0; i < numPoints; i++) {
		int i3 = i * 3;

		printf("          control point: %f %f %f\n", controlPoints[i3 + 0],
				controlPoints[i3 + 1], controlPoints[i3 + 2]);
	}

	return new Patch(order, partsU, partsV, compute, controlPoints, texture);
}

const vector<string> XMLParser::parseDescendants(TiXmlElement* element) {
	vector<string> descendantsIds;

	printf("    processing descendants:\n");

	// --- noderef --- //
	TiXmlElement* noderef = element->FirstChildElement("noderef");

	while (noderef) {
		descendantsIds.push_back(parseNodeRef(noderef));

		noderef = noderef->NextSiblingElement("noderef");
	}

	return descendantsIds;
}

const string XMLParser::parseNodeRef(TiXmlElement* element) {
	string id;

	// --- id --- //
	id = element->Attribute("id");

	printf("      noderef:\n");
	printf("        id: %s\n", id.c_str());

	return id;
}

void XMLParser::parseNodeDescendants(Node* node, Appearance* parentAppearance,
		bool isDisplayListContent) {
	// assure each node is only parsed once
	if (!node->getParsed()) {
		node->setParsed(true);

		glPushMatrix();
		glMultMatrixf(node->getTransforms().matrix);

		// create display list if node is a display list
		if (node->isDisplayList()) {
			node->setDisplayListID(glGenLists(1));
			glNewList(node->getDisplayListID(), GL_COMPILE);
		}

		if (node->isDisplayList() || isDisplayListContent)
			node->generateGeometry(parentAppearance);

		for (unsigned int i = 0; i < node->getDescendantsIds().size(); i++) {
			Node* descendant = nodes[node->getDescendantsIds()[i]];

			node->addDescendant(descendant);

			parseNodeDescendants(node->getDescendants()[i],
					node->getAppearance() ?
							node->getAppearance() : parentAppearance,
					node->isDisplayList() || isDisplayListContent);
		}

		if (node->isDisplayList())
			glEndList();

		glPopMatrix();
	}
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
