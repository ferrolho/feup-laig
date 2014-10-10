#include "Appearance.h"

Appearance::Appearance(const string& id, float shininess,
		const string& textureRef, const vector<RGBA*>& components) {
	this->id = id;
	this->shininess = shininess;
	this->textureRef = textureRef;
	this->components = components;
	this->appearance = buildAppearance(shininess, textureRef, components);
}

Appearance::~Appearance() {
}

string Appearance::getId() {
	return id;
}

CGFappearance* Appearance::buildAppearance(float shininess, string textureRef,
		const vector<RGBA*>& compenents) {
	RGB compAmb, compDif, compSpec;

	compAmb.rgb[0] = components[0]->getR();
	compAmb.rgb[1] = components[0]->getG();
	compAmb.rgb[2] = components[0]->getB();

	compDif.rgb[0] = components[1]->getR();
	compDif.rgb[1] = components[1]->getG();
	compDif.rgb[2] = components[1]->getB();

	compSpec.rgb[0] = components[2]->getR();
	compSpec.rgb[1] = components[2]->getG();
	compSpec.rgb[2] = components[2]->getB();

	CGFappearance* appTemp = new CGFappearance(compAmb.rgb, compDif.rgb,
			compSpec.rgb, shininess);

	return NULL;
}
