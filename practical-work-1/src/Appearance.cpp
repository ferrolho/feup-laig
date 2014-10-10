#include "Appearance.h"

Appearance::Appearance(string id, float shininess, string textureRef, vector<RGBA* > reflectionValues) {
	this->id = id;
	this->shininess = shininess;
	this->textureRef = textureRef;
	this->refletionValues = reflectionValues;
	this->appearance = buildAppearance(shininess, textureRef, reflectionValues);
}

Appearance::~Appearance() {

}

string Appearance::getId() {
	return id;
}

CGFappearance* Appearance::buildAppearance(float shininess, string textureRef, vector<RGBA* > reflectionValues) {
	RGB compAmb, compDif, compSpec;

	compAmb.rgb[0] = reflectionValues[0]->getR();
	compAmb.rgb[1] = reflectionValues[0]->getG();
	compAmb.rgb[2] = reflectionValues[0]->getB();

	compDif.rgb[0] = reflectionValues[1]->getR();
	compDif.rgb[1] = reflectionValues[1]->getG();
	compDif.rgb[2] = reflectionValues[1]->getB();

	compSpec.rgb[0] = reflectionValues[2]->getR();
	compSpec.rgb[1] = reflectionValues[2]->getG();
	compSpec.rgb[2] = reflectionValues[3]->getB();

	CGFappearance* appTemp = new CGFappearance(compAmb.rgb, compDif.rgb, compSpec.rgb, shininess);

	return NULL;
}
