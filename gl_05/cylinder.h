#pragma once
#include "mesh.h"

class Cylinder : public Mesh {
private:
	const int n = 60;
	void genVertices();
	void genIndices();
public:
	Cylinder(float, float);
	~Cylinder();
};