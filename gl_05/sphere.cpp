#include "sphere.h"

Sphere::Sphere(float radius) {
	width = radius * 2;
	height = radius * 2;
	genVertices();
	genIndices();
	for (auto i = 0; i < vertices.size() / 4; ++i) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	for (auto i = 0; i < vertices.size() / 4; ++i) {
		colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	for (auto i = 0; i < vertices.size() / 4; ++i) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	for (auto i = 0; i < vertices.size() / 4; ++i) {
		colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

Sphere::~Sphere() {
	
}

void Sphere::genVertices() {
	const int n = 38;
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 vectorTop(0.0f, width / 2.0f, 0.0f, 1.0f);
	glm::vec4 transformedVectorTop = vectorTop;
	for (int j = 1; j <= n / 2 + 1; ++j) {
		vertices.push_back(transformedVectorTop);
		for (int i = 0; i < n; ++i) {
			transformedVectorTop = rotate * transformedVectorTop;
			vertices.push_back(transformedVectorTop);
		}
		transformedVectorTop = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 1.0f, 0.0f)) * transformedVectorTop;
		rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-360.0f / float(n) * j), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n) * j), glm::vec3(0.0f, 1.0f, 0.0f));
	}

}

void Sphere::genIndices() {
	const int n = 38;
	for (int j = 0; j < n / 2; ++j) {
		for (int i = 0; i < n; ++i) {
			indices.push_back(i + 1 + (n + 1) * j);
			indices.push_back(i + n + 2 + (n + 1) * j);
			indices.push_back(i + 2 + (n + 1) * j);
			indices.push_back(i + 2 + (n + 1) * j);
			indices.push_back(i + n + 2 + (n + 1) * j);
			indices.push_back(i + n + 3 + (n + 1) * j);
		}
		indices.push_back(n + (n + 1) * j);
		indices.push_back(n + 1 + (n + 1) * j);
		indices.push_back(1 + (n + 1) * j);
		indices.push_back(1 + (n + 1) * j);
		indices.push_back(n + 1 + (n + 1) * j);
		indices.push_back(n + 2 + (n + 1) * j);
	}
}