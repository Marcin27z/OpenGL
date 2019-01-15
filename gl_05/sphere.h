#pragma once
#include "mesh.h"

class Sphere : public Mesh {
private:
	void genVertices();
	void genIndices();
public:
	Sphere(float);
	~Sphere();
	void cos();
};