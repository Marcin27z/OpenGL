#include "cone.h"

Cone::Cone(float radius, float height) {
	width = 2 * radius;
	this->height = height;
	depth = 2 * radius;
	genVertices();
	genIndices();
	for (auto && vertex : vertices) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	}
	colors[colors.size() - 1] = glm::vec3(1.0f, 0.0f, 0.0f);
	rotate(-90.0f, 0.0f, 0.0f);
}

Cone::~Cone() {

}

void Cone::genVertices() {
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec4 vectorTop(0.0f, width / 2.0f, -height / 2.0f, 1.0f);
	glm::vec4 transformedVectorTop = vectorTop;
	vertices.push_back(glm::vec4(0.0f, 0.0f, -height / 2.0f, 1.0f));
	vertices.push_back(vectorTop);
	for (int i = 1; i < n; i++) {
		transformedVectorTop = rotate * transformedVectorTop;
		vertices.push_back(transformedVectorTop);
	}
	vertices.push_back(glm::vec4(0.0f, 0.0f, height / 2.0f, 1.0f));
}

void Cone::genIndices() {
	for (int i = 0; i < n - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}
	indices.push_back(0);
	indices.push_back(n);
	indices.push_back(1);

	for (int i = 0; i < n - 1; i++) {
		indices.push_back(n + 1);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}
	indices.push_back(n + 1);
	indices.push_back(n);
	indices.push_back(1);
}

float Cone::getRadius() {
	return width / 2.0f;
}

float Cone::getHeight() {
	return height;
}