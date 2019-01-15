#include "texcube.h"
#include "shprogram.h"

void TexturedCube::genIndices() {
	// indices = {
	// 0, 1, 3,
	// 0, 3, 4,
	// 0, 4, 1,
	// 7, 4, 3,
	// 7, 4, 6,
	// 7, 3, 6,
	// 5, 4, 1,
	// 5, 6, 1,
	// 5, 4, 6,
	// 2, 6, 1,
	// 2, 3, 1,
	// 2, 3, 6
	// };
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

void TexturedCube::genVertices() {
	// vertices.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
	// vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
	// vertices.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
	// vertices.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	// vertices.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	// vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	// vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
	// vertices.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
	const int n = 80;
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 vectorTop(0.0f, 0.0f, width / 2.0f, 1.0f);
	glm::vec4 vectorOuter(0.0f, 0.0f, width / 2.0f + 0.25f, 1.0f);
	glm::vec4 transformedVectorTop = vectorTop;
	glm::vec4 transformedVectorOuter = vectorOuter;
	
	for (int j = 1; j <= n / 2 + 1; ++j) {
		vertices.push_back(transformedVectorTop);
		normals.push_back(glm::vec3(transformedVectorOuter));
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
			normals.push_back(glm::vec3(transformedVectorOuter));
		}
		transformedVectorTop = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f)) * transformedVectorTop;
		transformedVectorOuter = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f)) * transformedVectorOuter;
		rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-360.0f / float(n) * j), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n) * j), glm::vec3(0.0f, 0.0f, 1.0f));
	}	
	// const int n = 40;
	// glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 1.0f, 0.0f));
	// glm::vec4 vectorTop(0.0f, 0.0f, width / 2.0f, 1.0f);
	// glm::vec4 transformedVectorTop = vectorTop;
	// for (int j = 1; j <= n / 2 + 1; ++j) {
	// 	vertices.push_back(transformedVectorTop);
	// 	textures.push_back(glm::vec2(j < n / 4  ? 0 : 1, transformedVectorTop.y + 0.5f));
	// 	for (int i = 0; i < n; ++i) {
	// 		transformedVectorTop = rotate * transformedVectorTop;
	// 		textures.push_back(glm::vec2(j < n / 4 ? float(i + 1) / float(n) : float(n - i - 1) / float(n), transformedVectorTop.y + 0.5f));
	// 		vertices.push_back(transformedVectorTop);
	// 	}
	// 	transformedVectorTop = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f)) * transformedVectorTop;
	// 	rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-360.0f / float(n) * j), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n) * j), glm::vec3(0.0f, 0.0f, 1.0f));
	// }	
	// transformedVectorTop = vectorTop;
	// transformedVectorTop = vectorTop;
	// for (int j = 0; j <= n / 4 + 1; ++j) {
	// 	vertices.push_back(transformedVectorTop);
	// 	textures.push_back(glm::vec2(0, transformedVectorTop.z + 0.5f));
	// 	for (int i = 0; i < n; ++i) {
	// 		transformedVectorTop = rotate * transformedVectorTop;
	// 		textures.push_back(glm::vec2(float(i + 1) / float(n), transformedVectorTop.z + 0.5f));
	// 		vertices.push_back(transformedVectorTop);
	// 	}
	// 	transformedVectorTop = glm::rotate(glm::mat4(1.0f), glm::radians(-360.0f / float(n)), glm::vec3(1.0f, 0.0f, 0.0f)) * transformedVectorTop;
	// 	//rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-360.0f / float(n) * j), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n)), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / float(n) * j), glm::vec3(0.0f, 1.0f, 0.0f));
	// }
}

TexturedCube::TexturedCube(int width, int height, int depth) {
	this->width = width;
	this->height = height;
	this->depth = depth;
	genVertices();
	genIndices();
	for (auto i = 0; i < vertices.size(); ++i) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	texture = loadMipmapTexture(GL_TEXTURE0, "earth.png");
	// for (auto &tex: textures) {
	// 	std::cout << tex.x << " " << tex.y << std::endl;
	// }
	//scale(0.1f, 1.0f, 1.0f);
}

TexturedCube::~TexturedCube() {
}

void TexturedCube::draw(ShaderProgram theProgram) {
	
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
	// for (auto i = 4; i < 8; i++) {
	// 	tempVertices[i * 8 + 6] = -0.1f;
	// 	tempVertices[i * 8 + 7] = -0.1f;
	// }

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
