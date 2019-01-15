#include "ring.h"
#include "shprogram.h"

void Ring::genVertices() {
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f));

	/* Upper ring outer circle vertices */
	glm::vec4 vectorOuterTop(0.0f, outerRadius, height / 2.0f, 1.0f);
	glm::vec4 transformedVectorOuterTop = vectorOuterTop;
	glm::vec4 normalOuterTop(0.0f, outerRadius + 0.1f, height / 2.0f + 0.1f, 1.0f);
	glm::vec4 transformedNormalOuterTop = normalOuterTop;
	vertices.push_back(vectorOuterTop);
	normals.push_back(normalOuterTop);
	textures.push_back(glm::vec2(-0.1f, -0.1f));
	for (int i = 1; i < n; ++i) {
		transformedVectorOuterTop = rotate * transformedVectorOuterTop;
		transformedNormalOuterTop = rotate * transformedNormalOuterTop;
		vertices.push_back(transformedVectorOuterTop);
		normals.push_back(transformedNormalOuterTop);
		textures.push_back(glm::vec2(-0.1f, -0.1f));
	}
	/* Upper ring inner circle vertices */
	glm::vec4 vectorInnerTop(0.0f, innerRadius, height / 2.0f, 1.0f);
	glm::vec4 transformedVectorInnerTop = vectorInnerTop;
	glm::vec4 normalInnerTop(0.0f, innerRadius - 0.1f, height / 2.0f + 0.1f, 1.0f);
	glm::vec4 transformedNormalInnerTop = normalInnerTop;
	vertices.push_back(vectorInnerTop);
	normals.push_back(normalInnerTop);
	textures.push_back(glm::vec2(-0.1f, -0.1f));
	for (int i = 1; i < n; ++i) {
		transformedVectorInnerTop = rotate * transformedVectorInnerTop;
		transformedNormalInnerTop = rotate * transformedNormalInnerTop;
		vertices.push_back(transformedVectorInnerTop);
		normals.push_back(transformedNormalInnerTop);
		textures.push_back(glm::vec2(-0.1f, -0.1f));
	}
	/* Lower ring outer circle vertices */
	glm::vec4 vectorOuterBottom(0.0f, outerRadius, -height / 2.0f, 1.0f);
	glm::vec4 transformedVectorOuterBottom = vectorOuterBottom;
	glm::vec4 normalOuterBottom(0.0f, outerRadius + 0.1f, -height / 2.0f - 0.1f, 1.0f);
	glm::vec4 transformedNormalOuterBottom = normalOuterBottom;
	vertices.push_back(vectorOuterBottom);
	normals.push_back(normalOuterBottom);
	textures.push_back(glm::vec2(-0.1f, -0.1f));
	for (int i = 1; i < n; ++i) {
		transformedVectorOuterBottom = rotate * transformedVectorOuterBottom;
		transformedNormalOuterBottom = rotate * transformedNormalOuterBottom;
		vertices.push_back(transformedVectorOuterBottom);
		normals.push_back(transformedNormalOuterBottom);
		textures.push_back(glm::vec2(-0.1f, -0.1f));
	}
	/* Lower ring inner circle vertices */
	glm::vec4 vectorInnerBottom(0.0f, innerRadius, -height / 2.0f, 1.0f);
	glm::vec4 transformedVectorInnerBottom = vectorInnerBottom;
	glm::vec4 normalInnerBottom(0.0f, innerRadius - 0.1f,  -height / 2.0f - 0.1f, 1.0f);
	glm::vec4 transformedNormalInnerBottom = normalInnerBottom;
	vertices.push_back(vectorInnerBottom);
	normals.push_back(normalInnerBottom);
	textures.push_back(glm::vec2(-0.1f, -0.1f));
	for (int i = 1; i < n; ++i) {
		transformedVectorInnerBottom = rotate * transformedVectorInnerBottom;
		transformedNormalInnerBottom = rotate * transformedNormalInnerBottom;
		vertices.push_back(transformedVectorInnerBottom);
		normals.push_back(transformedNormalInnerBottom);
		textures.push_back(glm::vec2(-0.1f, -0.1f));
	}
}

void Ring::genIndices() {
	/* Upper ring indices*/
	for (int i = 0; i < n - 1; ++i) {
		indices.push_back(i);
		indices.push_back(i + n);
		indices.push_back(i + 1);
		indices.push_back(i + 1);
		indices.push_back(i + n);
		indices.push_back(i + n + 1);
	}
	indices.push_back(n - 1);
	indices.push_back(2 * n - 1);
	indices.push_back(0);
	indices.push_back(0);
	indices.push_back(2 * n - 1);
	indices.push_back(n);
	/* Lower ring indices*/
	for (int i = 2 * n; i < 3 * n - 1; ++i) {
		indices.push_back(i);
		indices.push_back(i + n);
		indices.push_back(i + 1);
		indices.push_back(i + 1);
		indices.push_back(i + n);
		indices.push_back(i + n + 1);
	}
	indices.push_back(3 * n - 1);
	indices.push_back(4 * n - 1);
	indices.push_back(2 * n);
	indices.push_back(2 * n);
	indices.push_back(4 * n - 1);
	indices.push_back(3 * n);
	/* */
	for (int i = 0; i < n - 1; ++i) {
		indices.push_back(i);
		indices.push_back(i + 2 * n);
		indices.push_back(i + 1);
		indices.push_back(i + 1);
		indices.push_back(i + 2 * n);
		indices.push_back(i + 2 * n + 1);
	}
	indices.push_back(n - 1);
	indices.push_back(3 * n - 1);
	indices.push_back(0);
	indices.push_back(0);
	indices.push_back(3 * n - 1);
	indices.push_back(2 * n);
	/* */
	for (int i = 0; i < n - 1; ++i) {
		indices.push_back(i + n);
		indices.push_back(i + 3 * n);
		indices.push_back(i + 1 + n);
		indices.push_back(i + 1 + n);
		indices.push_back(i + 3 * n);
		indices.push_back(i + 3 * n + 1);
	}
	indices.push_back(2 * n - 1);
	indices.push_back(4 * n - 1);
	indices.push_back(n);
	indices.push_back(n);
	indices.push_back(4 * n - 1);
	indices.push_back(3 * n);
}

Ring::Ring(float innerRadius, float outerRadius, float height) {
	this->innerRadius = innerRadius;
	this->outerRadius = outerRadius;
	this->height = height;
	this->width = 2 * outerRadius;
	this->depth = 2 * outerRadius;
	genVertices();
	genIndices();
	for (auto i = 0; i < vertices.size(); ++i) {
		colors.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	}
	// for (auto i = 0; i < vertices.size() / 4; ++i) {
	// 	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// }
	// for (auto i = 0; i < vertices.size() / 4; ++i) {
	// 	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	// }
	// for (auto i = 0; i < vertices.size() / 4; ++i) {
	// 	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// }
	//rotate(-90.0f, 0.0f, 0.0f);
}

Ring::~Ring() {

}

float Ring::getOuterRadius() {
	return outerRadius;
}

float Ring::getInnerRadius() {
	return innerRadius;
}

void Ring::draw(ShaderProgram theProgram) {

	auto verticesIterator = vertices.begin();
	auto colorsIterator = colors.begin();
	auto texturesIterator = textures.end();
	auto normalsIterator = normals.begin();
	GLfloat* tempVertices = new GLfloat[vertices.size() * 3 + colors.size() * 3 + textures.size() * 2 + normals.size() * 3];
	for (auto i = 0; i < vertices.size(); i++) {
		--texturesIterator;
		tempVertices[i * 11] = (*verticesIterator).x;
		tempVertices[i * 11 + 1] = (*verticesIterator).y;
		tempVertices[i * 11 + 2] = (*verticesIterator).z;
		tempVertices[i * 11 + 3] = (*colorsIterator).x;
		tempVertices[i * 11 + 4] = (*colorsIterator).y;
		tempVertices[i * 11 + 5] = (*colorsIterator).z;
		tempVertices[i * 11 + 6] = (*texturesIterator).x;
		tempVertices[i * 11 + 7] = (*texturesIterator).y;
		tempVertices[i * 11 + 8] = (*normalsIterator).x;
		tempVertices[i * 11 + 9] = (*normalsIterator).y;
		tempVertices[i * 11 + 10] = (*normalsIterator).z;
		++verticesIterator;
		++colorsIterator;
		++normalsIterator;
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 11 * sizeof(GLfloat), tempVertices, GL_STATIC_DRAW);

	delete[] tempVertices;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint* tempIndices = new GLuint[indices.size()];
	std::copy(indices.begin(), indices.end(), tempIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), tempIndices, GL_STATIC_DRAW);

	delete[] tempIndices;

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
	glUniform3fv(glGetUniformLocation(theProgram.get_programID(), "lightColor"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(glGetUniformLocation(theProgram.get_programID(), "lightPos"), 1, glm::value_ptr(glm::vec3(0.0f, -10.0f, 0.0f)));
	// prepare textures
	// theProgram->Use();
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}

