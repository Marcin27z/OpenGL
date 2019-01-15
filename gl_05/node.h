#pragma once

class Node {
protected:
	float positionX, positionY, positionZ;
	float width, height, depth;
	float velocityX, velocityY, velocityZ; //to be used later
	float angularSpeedX, angularSpeedY, angularSpeedZ; //to be used later
	float angleX, angleY, angleZ;
public:
	Node();
	~Node();
	virtual void draw() = 0;
	virtual void scale(float, float, float) = 0;
	virtual void scale(float, float, float, float, float, float) = 0;
	virtual void move(float, float, float) = 0;
	virtual void rotate(float, float, float) = 0;
	virtual void rotate(float, float, float, float, float, float) = 0;
	float getX();
	float getY();
	float getZ();
	float getWidth();
	float getHeight();
	float getDepth();
	float getAngularSpeedX();
	float getAngularSpeedY();
	float getAngularSpeedZ();
	void setAngularSpeedX(float);
	void setAngularSpeedY(float);
	void setAngularSpeedZ(float);
};