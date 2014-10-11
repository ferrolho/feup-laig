#pragma once

#include "Drawing.h"

class Globals {
private:
	Drawing* drawing;

public:
	Globals();
	Globals(Globals* globals);
	Globals(Drawing* drawing);
	virtual ~Globals();

	Drawing* getDrawing();
	void setDrawing(Drawing* drawing);
};
