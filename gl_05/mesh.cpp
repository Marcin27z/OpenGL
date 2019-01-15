#include "mesh.h"
#include <GLFW/glfw3.h>

Mesh::Mesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::draw() {
	
	auto verticesIterator = vertices.begin();
	auto colorsIterator = colors.begin();
	GLfloat* tempVertices = new GLfloat[vertices.size() * 3 + colors.size() * 3];
	for (int i = 0; i < vertices.size(); i++) {
		tempVertices[i * 6] = (*verticesIterator).x;
		tempVertices[i * 6 + 1] = (*verticesIterator).y;
		tempVertices[i * 6 + 2] = (*verticesIterator).z;
		tempVertices[i * 6 + 3] = (*colorsIterator).x;
		tempVertices[i * 6 + 4] = (*colorsIterator).y;
		tempVertices[i * 6 + 5] = (*colorsIterator).z;
		verticesIterator++;
		colorsIterator++;
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 6 * sizeof(GLfloat), tempVertices, GL_STATIC_DRAW);

	delete[] tempVertices;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint* tempIndices = new GLuint[indices.size()];
	std::copy(indices.begin(), indices.end(), tempIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), tempIndices, GL_STATIC_DRAW);

	delete[] tempIndices;

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::setColor(float r, float g, float b) {
	for (auto && color : colors) {
		color = glm::vec3(r, g, b);
	}
}

void Mesh::scale(float xScale, float yScale, float zScale) {
	scale(xScale, yScale, zScale, positionX, positionY, positionZ);
}

void Mesh::scale(float xScale, float yScale, float zScale, float xPivot, float yPivot, float zPivot) {
	width *= xScale;
	height *= yScale;
	depth *= zScale;
	//glm::mat4 moveCenter = glm::translate(glm::mat4(1.0f), glm::vec3(-xPivot, -yPivot, -zPivot));
	//glm::mat4 moveBack = glm::translate(glm::mat4(1.0f), glm::vec3(xPivot, yPivot, zPivot));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(xScale, yScale, zScale));
	for (auto && vertex : vertices) {
		//vertex = moveCenter * scale * moveBack * vertex;
		vertex = scale * vertex;
	}
}

void Mesh::move(float xMove, float yMove, float zMove) {
	positionX += xMove;
	positionY += yMove;
	positionZ += zMove;
	glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(xMove, yMove, zMove));
	for (auto && vertex : vertices) {
		vertex = move * vertex;
	}
}

void Mesh::rotate(float xAngle, float yAngle, float zAngle) {
	rotate(xAngle, yAngle, zAngle, positionX, positionY, positionZ);
}

void Mesh::rotate(float xAngle, float yAngle, float zAngle, float xPivot, float yPivot, float zPivot) {
	angleX += xAngle;
	angleY += yAngle;
	angleZ += zAngle;
	using glm::mat4;
	using glm::vec3;
	glm::mat4 moveCenter = glm::translate(glm::mat4(1.0f), glm::vec3(-xPivot, -yPivot, -zPivot));
	glm::mat4 moveBack = glm::translate(glm::mat4(1.0f), glm::vec3(xPivot, yPivot, zPivot));
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(xAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(yAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(zAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotate = moveBack * rotateX * rotateY * rotateZ * moveCenter;
	for (auto && vertex : vertices) {
		vertex = rotate * vertex;
	}
}

GLuint Mesh::loadMipmapTexture(GLuint texId, const char* fname) {
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void Mesh::assign(Mesh &other) {
	positionX = other.positionX;
	positionY = other.positionY;
	positionZ = other.positionZ;
	width = other.width;
	height = other.height;
	depth = other.depth;
	VBO = other.VBO;
	VAO = other.VAO;
	EBO = other.EBO;
	vertices = other.vertices;
	colors = other.colors;
	indices = other.indices;
}

