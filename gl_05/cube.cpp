#include "cube.h"

Cube::Cube(float width, float height, float depth) {
	genVertices();
	genIndices();
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	scale(width, height, depth);
	this->width = width;
	this->height = height;
	this->depth = depth;
}

Cube::~Cube() {

}

Cube::Cube() {

}

void Cube::genVertices() {
	vertices.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
	vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
	vertices.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
	vertices.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	vertices.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
	vertices.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
}

void Cube::genIndices() {
	indices = {
		0, 1, 3,
		0, 3, 4,
		0, 4, 1,
		7, 4, 3,
		7, 4, 6,
		7, 3, 6,
		5, 4, 1,
		5, 6, 1,
		5, 4, 6,
		2, 6, 1,
		2, 3, 1,
		2, 3, 6
	};
}

Cube& Cube::operator=(Cube other) {
	assign(other);
	return *this;
}