#include "group.h"
#include <GLFW/glfw3.h>

Group::Group() {

}

Group::~Group() {

}

void Group::move(float xMove, float yMove, float zMove) {
	positionX += xMove;
	positionY += yMove;
	positionZ += zMove;
	for (auto && object : objects) {
		(*object).move(xMove, yMove, zMove);
	}
}

void Group::rotate(float xAngle, float yAngle, float zAngle) {
	angleX += xAngle;
	angleY += yAngle;
	angleZ += zAngle;
	for (auto && object : objects) {
		(*object).rotate(xAngle, yAngle, zAngle);
	}
}

void Group::rotate(float xAngle, float yAngle, float zAngle, float xPivot, float yPivot, float zPivot) {
	angleX += xAngle;
	angleY += yAngle;
	angleZ += zAngle;
	for (auto && object : objects) {
		(*object).rotate(xAngle, yAngle, zAngle, xPivot, yPivot, zPivot);
	}
}

void Group::draw() {
	for (auto && object : objects) {
		(*object).draw();
	}
}

void Group::scale(float xScale, float yScale, float zScale) {
	width *= xScale;
	height *= yScale;
	depth *= zScale;
	for (auto object : objects) {
		(*object).scale(xScale, yScale, zScale, positionX, positionY, positionZ);
	}
}

void Group::scale(float xScale, float yScale, float zScale, float xPivot, float yPivot, float zPivot) {
	width *= xScale;
	height *= yScale;
	depth *= zScale;
	for (auto object : objects) {
		(*object).scale(xScale, yScale, zScale, xPivot, yPivot, zPivot);
	}
}
/*
void Group::action(void (Mesh::* function)(float x, float y, float z)) {
	for (auto && object : objects) {
		(object.*function)(x, y, z);
	}
}*/

void Group::add(Node *object) {
	objects.push_back(object);
}