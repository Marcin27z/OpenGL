#include "circle.h"

Circle::Circle(float radius) {
	this->width = radius * 2.0f;
	this->depth = radius * 2.0f;
	genVertices();
	genIndices();
	for (int i = 0; i < n + 1; ++i) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	}
}

Circle::~Circle() {

}

void Circle::genVertices() {
	glm::vec4 vector(0.0f, width / 2.0f, 0.0f, 1.0f);
	glm::vec4 transformedVector = vector;
	vertices.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	vertices.push_back(vector);
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f));
	for (int i = 1; i < n; ++i) {
		transformedVector = rotate * transformedVector;
		vertices.push_back(transformedVector);
	}
}

void Circle::genIndices() {
	for (int i = 0; i < n - 1; ++i) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}
	indices.push_back(0);
	indices.push_back(n);
	indices.push_back(1);
}