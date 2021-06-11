#pragma once
#include <d2d1.h>
#include "ObjectBase.h"

class Circle : public ObjectBase{
public:
	Circle(double x, double y, float radius);
	Circle(double x, double y, float radius, float stroke);

	void draw(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brush);

	void logic();


	float stroke = 2.0f, radius = 0;
	double speedX = 10, speedY = 10;
};