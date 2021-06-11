#pragma once
#include "ObjectBase.h"

class Poly : public ObjectBase {
public:
	Poly(double x, double y, int polyPoints);

	void logic();

	void draw(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brush);

	double speedX = 10, speedY = 10;
	float stroke = 2.0f;	
};