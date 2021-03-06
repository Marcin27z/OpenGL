#include "skybox.h"

void Skybox::genIndices() {

	const int n = 80;
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

void Skybox::genVertices() {
	const int n = 80;
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 vectorTop(0.0f, 0.0f, width / 2.0f, 1.0f);
	glm::vec4 vectorOuter(0.0f, 0.0f, width / 2.0f + 0.25f, 1.0f);
	glm::vec4 transformedVectorTop = vectorTop;
	glm::vec4 transformedVectorOuter = vectorOuter;

	for (int j = 1; j <= n / 2 + 1; ++j) {
		vertices.push_back(transformedVectorTop);
		textures.push_back(glm::vec2(float(j) / float(n), 0));
		for (int i = 0; i < n; ++i) {
			transformedVectorTop = rotate * transformedVectorTop;
			transformedVectorOuter = rotate * transformedVectorOuter;
			if (i >= n / 2) {
				textures.push_back(glm::vec2(float(j) / float(n), float(n - i - 1) / float(n / 2)));
			} else {
				textures.push_back(glm::vec2(float(j) / float(n) + 0.5f, float(i + 1) / float(n / 2)));
			}
			vertices.push_back(transformedVectorTop);
		}
		transformedVectorTop = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f)) * transformedVectorTop;
		transformedVectorOuter = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f)) * transformedVectorOuter;
		rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-360.0f / float(n) * j), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n) * j), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

Skybox::Skybox(int radius) {
	this->width = 2 * radius;
	this->height = 2 * radius;
	this->depth = 2 * radius;
	genVertices();
	genIndices();
	for (auto i = 0; i < vertices.size(); ++i) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	texture = loadMipmapTexture(GL_TEXTURE0, "skybox.jpg");
}

Skybox::~Skybox() {
}

void Skybox::draw(ShaderProgram theProgram) {

	auto verticesIterator = vertices.begin();
	auto colorsIterator = colors.begin();
	auto texturesIterator = textures.end();
	GLfloat* tempVertices = new GLfloat[vertices.size() * 3 + colors.size() * 3 + textures.size() * 2];
	for (auto i = 0; i < vertices.size(); i++) {
		--texturesIterator;
		tempVertices[i * 8] = (*verticesIterator).x;
		tempVertices[i * 8 + 1] = (*verticesIterator).y;
		tempVertices[i * 8 + 2] = (*verticesIterator).z;
		tempVertices[i * 8 + 3] = (*colorsIterator).x;
		tempVertices[i * 8 + 4] = (*colorsIterator).y;
		tempVertices[i * 8 + 5] = (*colorsIterator).z;
		tempVertices[i * 8 + 6] = (*texturesIterator).x;
		tempVertices[i * 8 + 7] = (*texturesIterator).y;
		++verticesIterator;
		++colorsIterator;
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 8 * sizeof(GLfloat), tempVertices, GL_STATIC_DRAW);

	delete[] tempVertices;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint* tempIndices = new GLuint[indices.size()];
	std::copy(indices.begin(), indices.end(), tempIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), tempIndices, GL_STATIC_DRAW);

	delete[] tempIndices;

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
	// prepare textures
	// theProgram->Use();
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}
