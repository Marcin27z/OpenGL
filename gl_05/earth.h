#pragma once

#include "mesh.h"
#include "shprogram.h"

class Earth : public Mesh {
private:
	void genIndices();
	void genVertices();
	std::vector<glm::vec3> normals;
public:
	Earth(int);
	~Earth();
	void draw(ShaderProgram);
};