#pragma once
#include "mesh.h"

class Circle : public Mesh {
private:
	const int n = 36;
	void genVertices();
	void genIndices();
public:
	Circle(float);
	~Circle();
};
