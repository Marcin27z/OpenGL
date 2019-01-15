#pragma once
#include "mesh.h"

class ShaderProgram;

class Ring : public Mesh {
private:
	const int n = 36;
	float innerRadius;
	float outerRadius;
	void genVertices();
	void genIndices();
public:
	Ring(float, float, float);
	~Ring();
	void draw(ShaderProgram);
	float getOuterRadius();
	float getInnerRadius();
};
