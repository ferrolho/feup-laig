#pragma once

#include <map>
#include <string>
#include <vector>
#include "Appearance.h"
#include "Cameras.h"
#include "Components.h"
#include "Cylinder.h"
#include "Flag.h"
#include "Globals.h"
#include "Light.h"
#include "Lights.h"
#include "Patch.h"
#include "Plane.h"
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
#include "Animation.h"
#include "TriangularPrism.h"

using namespace std;

class XMLParser {
public:
	XMLParser(const char* filename, Globals& globals, Cameras& cameras,
			Lights& lights, map<string, Appearance*>& appearances, SceneGraph* graph);
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
	TiXmlElement* animationsElement;
	TiXmlElement* graphElement;

private:
	string rootid;
	map<string, Node*> nodes;
	map<string, Texture*> textures;
	map<string, Appearance*> appearances;
	map<string, Animation*> animations;

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

	void parseTextures(SceneGraph* graph);
	Texture* parseTexture(TiXmlElement* element);

	map<string, Appearance*> parseAppearances();
	Appearance* parseAppearance(TiXmlElement* element);
	Components* parseAppearanceComponents(TiXmlElement* element);

	void parseAnimations();
	Animation* parseAnimation(TiXmlElement* element);
	LinearAnimation* parseLinearAnimation(TiXmlElement* element, string id,
			float span);
	Point3D* parseControlPoint(TiXmlElement* element);
	CircularAnimation* parseCircularAnimation(TiXmlElement* element, string id,
			float span);

	void parseGraph(SceneGraph* graph);
	void parseNode(TiXmlElement* element);

	Matrix* parseTransforms(TiXmlElement* element);
	Transform* parseTransform(TiXmlElement* element);
	Translation* parseTranslate(TiXmlElement* element);
	Rotation* parseRotate(TiXmlElement* element);
	Scaling* parseScale(TiXmlElement* element);

	Appearance* parseAppearanceRef(TiXmlElement* element);
	Animation* parseAnimationRef(TiXmlElement* element);

	vector<Primitive*>* parsePrimitives(TiXmlElement* element,
			Texture* texture = NULL);
	Rectangle* parseRectangle(TiXmlElement* primitive, Texture* texture = NULL);
	Triangle* parseTriangle(TiXmlElement* primitive, Texture* texture = NULL);
	Cylinder* parseCylinder(TiXmlElement* primitive);
	Sphere* parseSphere(TiXmlElement* primitive);
	Torus* parseTorus(TiXmlElement* primitive);
	Plane* parsePlane(TiXmlElement* primitive, Texture* texture = NULL);
	Patch* parsePatch(TiXmlElement* primitive, Texture* texture = NULL);
	Flag* parseFlag(TiXmlElement* primitive);
	TriangularPrism* parseTriangularPrism(TiXmlElement* primitive, Texture* texture = NULL);

	vector<string>* parseDescendants(TiXmlElement* element);
	const string parseNodeRef(TiXmlElement* element);

	void parseNodeDescendants(Node* node, Appearance* parentAppearance,
			bool isDisplayListContent);
};
