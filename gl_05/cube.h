#pragma once
#include "mesh.h"

class Cube : public Mesh {
private:
	void genVertices();
	void genIndices();
public:
	Cube(float, float, float);
	Cube();
	~Cube();
	Cube& operator=(Cube);
};