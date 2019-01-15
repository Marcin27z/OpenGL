#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"
#include "circle.h"
#include "cube.h"
#include "cylinder.h"
#include "cone.h"
#include "ring.h"
#include "group.h"
#include "texcube.h"
#include "sphere.h"
#include "cog.h"
#include <vector>
#include "skybox.h"
#include "earth.h"

using namespace std;

const GLuint WIDTH = 800, HEIGHT = 800;

static GLfloat cameraRotationAngleX = 0.0f;
static GLfloat cameraRotationAngleY = 0.0f;
static GLfloat zoom = -3.0f;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
		cameraRotationAngleX += 1.0f;
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
		cameraRotationAngleX -= 1.0f;
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
		cameraRotationAngleY -= 1.0f;
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		cameraRotationAngleY += 1.0f;
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_REPEAT)
		zoom -= 1.0f;
	if (key == GLFW_KEY_KP_ADD && action == GLFW_REPEAT)
		zoom += 1.0f;
}

double mouseOldPosX, mouseOldPosY;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &mouseOldPosX, &mouseOldPosY);
	}
}

void cursorCallback(GLFWwindow* window, double mousePosX, double mousePosY) {
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS) {
		cameraRotationAngleX += mousePosX - mouseOldPosX;
		cameraRotationAngleY += mousePosY - mouseOldPosY;
		mouseOldPosX = mousePosX;
		mouseOldPosY = mousePosY;
	}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	if (zoom + yoffset < -0.5f && zoom + yoffset > -20.0f)
		zoom += yoffset;
}

GLuint loadMipmapTexture(GLuint texId, const char* fname) {
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

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

ostream& operator<<(ostream& os, const glm::mat4& mx) {
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}

int main() {
	if (glfwInit() != GL_TRUE) {
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try {
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Kolo", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetCursorPosCallback(window, cursorCallback);
		glfwSetScrollCallback(window, scrollCallback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);
		glEnable(GL_DEPTH_TEST);

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_05.vert", "tex.frag");
		ShaderProgram theProgram2("gl_05.vert", "gl_05.frag");
		ShaderProgram skyboxProgram("gl_05.vert", "skybox.frag");
		
		Cube cube(0.5f, 1.0f, 0.5f);
		Cone cone(0.375f, 0.5f);
		cone.move(0.0f, cube.getHeight() / 2.0f + cone.getHeight() / 2.0f, 0.0f);
		Cylinder cylinder(0.2f, 0.1f);
		cylinder.rotate(270.0f, 0.0f, 0.0f);
		cylinder.move(0.0f, cube.getHeight() / 4.0f, -cube.getDepth() / 2.0f - cylinder.getHeight() / 2.0f);
		Cube cube2(0.025f, 0.1f, 0.025f);
		cube2.setColor(0.0f, 1.0f, 0.0f);
		cube2.move(0.0f, cube.getHeight() / 4.0f + cube2.getHeight() / 2.0f, -cube.getDepth() / 2.0f - cylinder.getHeight() - cube2.getDepth());
		
		Cylinder axis(0.08f, 0.75f);
		Circle circle(360);

		TexturedCube tex(1.0f, 1.0f, 1.0f);
		TexturedCube tex2(1.0f, 1.0f, 1.0f);
		tex2.move(0.5f, 0.0f, 0.0f);
		tex2.texture = tex2.loadMipmapTexture(GL_TEXTURE0, "iipw.png");

		Ring chainLink(0.5f, 0.75f, 0.3f);
		chainLink.scale(2.0f, 1.0f, 1.0f);

		Sphere sphere(0.7f);
		sphere.rotate(0.0f, 0.0f, 20.0f);
		Ring ring(0.8f, 1.0f, 0.1f);
		//glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f)) * glm::rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//sphere.cos();

		Cog cog(36, 1.0f);
		Cog cog2(12, 1.0f);
		Cog cog3(24, 1.0f);
		cog.setAngularSpeed(20.0f);
		cog2.synchronizeSpeed(cog);
		cog3.synchronizeSpeed(cog);
		cog2.rotate(0.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		cog3.rotate(0.0f, 7.5f, 0.0f, 0.0f, 0.0f, 0.0f);
		cog2.move(cog.getRadius() + cog2.getRadius() + 0.1f, 0.0f, 0.0f);
		cog3.move(0.0f, 0.0f, cog.getRadius() + cog3.getRadius() + 0.1f);
		tex.rotate(-90.0f, 0.0f, 0.0f);

		Skybox skybox(40.0f);
		skybox.rotate(-90.0f, 0.0f, 0.0f);
		Earth earth(1.0f);
		earth.rotate(-90.0f, 0.0f, 0.0f);
		Circle floor(40.0f);
		floor.rotate(-90.0f, 0.0f, 0.0f);
		floor.move(0.0f, -1.0f, 0.0f);
		floor.setColor(0.0f, 1.0f, 0.5f);
		Ring ring2(1.0f, 0.5f, 0.3f);

		// main event loop
		while (!glfwWindowShouldClose(window)) {
		
			static float deltaTime = 0.0f, lastFrame = 0.0f;
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 viewX;
			glm::mat4 viewY;
			glm::mat4 projection;
			glm::mat4 transform;
			glm::mat4 view;
			projection = glm::perspective(glm::radians(60.0f), GLfloat(WIDTH) / GLfloat(HEIGHT), 0.1f, 100.0f);
			viewX = glm::rotate(viewX, -glm::radians(cameraRotationAngleX), glm::vec3(0.0, 1.0, 0.0));
			viewY = glm::rotate(viewY, -glm::radians(cameraRotationAngleY), glm::vec3(1.0, 0.0, 0.0));
			GLuint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
			GLuint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
			GLuint projectionLoc2 = glGetUniformLocation(theProgram2.get_programID(), "projection");
			GLuint viewLoc2 = glGetUniformLocation(theProgram2.get_programID(), "view");
			GLuint transformLoc2 = glGetUniformLocation(theProgram2.get_programID(), "transform");
			//transform = viewX * viewY;
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, zoom)) * viewX * viewY;
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

			theProgram.Use();
			glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform));


			earth.draw(theProgram);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
	}
	catch (exception ex) {
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}