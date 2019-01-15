#pragma once

#include "mesh.h"
#include "shprogram.h"

class Skybox : public Mesh {
private:
	void genIndices();
	void genVertices();
public:
	Skybox(int);
	~Skybox();
	void draw(ShaderProgram);
};