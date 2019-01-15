#include "cog.h"

Cog::Cog(int teethNumber, float size) {
	ringOuter = new Ring (0.5f, 0.75f, 0.3f);
	ringInner = new Ring (0.1f, 0.25f, 0.3f);
	arms[0] = Cube(0.4f, 0.25f, 0.25f);
	arms[1] = Cube(0.4f, 0.25f, 0.25f);
	arms[2] = Cube(0.25f, 0.25f, 0.4f);
	arms[3] = Cube(0.25f, 0.25f, 0.4f);
	arms[0].move(0.25f + arms[0].getDepth() / 2.0f, 0.0f, 0.0f);
	arms[1].move(-0.25f - arms[1].getDepth() / 2.0f, 0.0f, 0.0f);
	arms[2].move(0.0f, 0.0f, 0.25f + arms[2].getWidth() / 2.0f);
	arms[3].move(0.0f, 0.0f, -0.25f - arms[3].getWidth() / 2.0f);
	addAll(ringOuter, ringInner, &arms[0], &arms[1], &arms[2], &arms[3]);
	float ratio = float(teethNumber) / 24.0f;
	for (int i = 0; i < teethNumber; i++) {
		Cube *cube2 = new Cube(0.1f / ratio, 0.29f, 0.1f / ratio);
		cube2->move(0.0f, 0.0f, 0.75f + 0.05f / ratio);
		cube2->rotate(0.0f, 360.0f / float(teethNumber) * i, 0.0f, 0.0f, 0.0f, 0.0f);
		add(cube2);
		teeth.push_back(cube2);
	}
	angularSpeed = 0.0f;
	scale(ratio, 1.0f, ratio);
	scale(size, size, size);
	radius = 0.75f * ratio * size;
}

Cog::~Cog() {
	
}

void Cog::draw(float deltaTime) {
	float tmpAngleX = angleX, tmpAngleZ = angleZ;
	rotate(-angleX, 0.0f, -angleZ, positionX, positionY, positionZ);
	rotate(0.0f, angularSpeed * deltaTime, 0.0f, positionX, positionY, positionZ);
	rotate(tmpAngleX, 0.0f, tmpAngleZ, positionX, positionY, positionZ);
	Group::draw();
}

void Cog::setAngularSpeed(float angularSpeed) {
	this->angularSpeed = angularSpeed;
}

void Cog::synchronizeSpeed(const Cog &other) {
	angularSpeed = -other.angularSpeed * other.teeth.size() / teeth.size();
}

float Cog::getRadius() {
	return radius;
}