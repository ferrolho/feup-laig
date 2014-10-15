#pragma once

#include "Culling.h"
#include "Drawing.h"
#include "Lighting.h"

class Globals {
private:
	Drawing* drawing;
	Culling* culling;
	Lighting* lighting;

public:
	Globals();
	Globals(Globals* globals);
	Globals(Drawing* drawing, Culling* culling, Lighting* lighting);
	virtual ~Globals();

	Culling* getCulling();
	Drawing* getDrawing();
	Lighting* getLighting();
	void setCulling(Culling* culling);
	void setDrawing(Drawing* drawing);
	void setLighting(Lighting* lighting);
};
