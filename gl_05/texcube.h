#pragma once

#include "mesh.h"
#include "shprogram.h"

class TexturedCube : public Mesh {
	
private:
	void genIndices();
	void genVertices();
	ShaderProgram *theProgram;
	std::vector<glm::vec3> normals;
public:
	TexturedCube(int, int, int);
	~TexturedCube();
	void draw(ShaderProgram);
};