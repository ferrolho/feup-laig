#pragma once

#include <vector>
using namespace std;

class SceneGraph {
private:
	vector<Primitive> primitives;
public:
	SceneGraph();
	virtual ~SceneGraph();
};
