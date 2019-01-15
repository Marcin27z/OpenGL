#include "cylinder.h"

Cylinder::Cylinder(float radius, float height) {
	width = 2 * radius;
	this->height = height;
	depth = 2 * radius;
	genVertices();
	genIndices();
	/*for (auto && vertex : vertices) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	}*/
	for (int i = 0; i < vertices.size() / 2; ++i) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	for (int i = 0; i < vertices.size() / 2; ++i) {
		colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	}
	rotate(-90.0f, 0.0f, 0.0f);
}

Cylinder::~Cylinder() {

}

void Cylinder::genVertices() {
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec4 vectorTop(0.0f, width / 2.0f, height / 2.0f, 1.0f);
	glm::vec4 transformedVectorTop = vectorTop;
	vertices.push_back(glm::vec4(0.0f, 0.0f, height / 2.0f, 1.0f));
	vertices.push_back(vectorTop);
	for (int i = 1; i < n; ++i) {
		transformedVectorTop = rotate * transformedVectorTop;
		vertices.push_back(transformedVectorTop);
	}

	glm::vec4 vectorBottom(0.0f, width / 2.0f, -height / 2.0f, 1.0f);
	glm::vec4 transformedVectorBottom = vectorBottom;
	vertices.push_back(glm::vec4(0.0f, 0.0f, -height / 2.0f, 1.0f));
	vertices.push_back(vectorBottom);
	for (int i = 1; i < n; ++i) {
		transformedVectorBottom = rotate * transformedVectorBottom;
		vertices.push_back(transformedVectorBottom);
	}
}

void Cylinder::genIndices() {
	for (int i = 0; i < n - 1; ++i) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}
	indices.push_back(0);
	indices.push_back(n);
	indices.push_back(1);

	for (int i = n + 1; i < 2 * n; ++i) {
		indices.push_back(n + 1);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}
	indices.push_back(n + 1);
	indices.push_back(2 * n + 1);
	indices.push_back(n + 2);

	for (int i = 0; i < n - 1; ++i) {
		indices.push_back(i + 1);
		indices.push_back(i + n + 2);
		indices.push_back(i + 2);
		indices.push_back(i + 2);
		indices.push_back(i + n + 2);
		indices.push_back(i + n + 3);
	}
	indices.push_back(n);
	indices.push_back(2 * n + 1);
	indices.push_back(1);
	indices.push_back(1);
	indices.push_back(2 * n + 1);
	indices.push_back(n + 2);
}