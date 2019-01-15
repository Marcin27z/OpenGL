#include "node.h"

Node::Node(): angularSpeedX(0.0f), angularSpeedY(0.0f), angularSpeedZ(0.0f) {
	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;
	angleX = 0.0f;
	angleY = 0.0f;
	angleZ = 0.0f;
}

Node::~Node() {

}

float Node::getX() {
	return positionX;
}

float Node::getY() {
	return positionY;
}

float Node::getZ() {
	return positionZ;
}

float Node::getWidth() {
	return width;
}

float Node::getHeight() {
	return height;
}

float Node::getDepth() {
	return depth;
}

float Node::getAngularSpeedX() {
	return angularSpeedX;
}

float Node::getAngularSpeedY() {
	return angularSpeedY;
}

float Node::getAngularSpeedZ() {
	return angularSpeedZ;
}

void Node::setAngularSpeedX(float angularSpeedX) {
	this->angularSpeedX = angularSpeedX;
}

void Node::setAngularSpeedY(float angularSpeedY) {
	this->angularSpeedY = angularSpeedY;
}

void Node::setAngularSpeedZ(float angularSpeedZ) {
	this->angularSpeedZ = angularSpeedZ;
}


