#pragma once
#include <d2d1.h>
#include "Point.h"
#include <iostream>

class ObjectBase {
public:

	virtual void logic();

	virtual void logic(double elapsedTIme);

	virtual void draw(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brush);

	void calcRotation();

	Point getPosition();

	Point* getRotatedPoints();

	int getNumberOfPoints();

	float radius = 50;

protected:

	Point position;

	Point *rotatedPolyPoints;
	Point *polyPoints;

	int pointsN;

	double speedX, speedY;
	double rotation = 0, oldRotation = -1;

	float stroke, rotationSpeed = 0.01;

	
};