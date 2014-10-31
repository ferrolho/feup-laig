#pragma once

#include "TransformType.h"

class Transform {
private:
	TransformType type;

public:
	Transform(TransformType type);
	virtual ~Transform();

	virtual void apply() = 0;
};
