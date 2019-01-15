#pragma once
#pragma once
#include "mesh.h"

class Cone : public Mesh {
private:
	const int n = 360;
	void genVertices();
	void genIndices();
public:
	Cone(float, float);
	~Cone();
	float getHeight();
	float getRadius();
};