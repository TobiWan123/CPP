#include "Circle.h"
#include <iostream>

Circle::Circle(double x, double y, float radius) {
	position.x = x;
	position.y = y;
	Circle::radius = radius;
}

Circle::Circle(double x, double y, float radius, float stroke) {
	position.x = x;
	position.y = y;
	Circle::radius = radius;
	Circle::stroke = stroke;
}

void Circle::draw(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brush) {
	renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(position.x, position.y), radius, radius), brush);
}

void Circle::logic(){
	if (position.x+radius >= 600) speedX = -((rand() + 1) % 20);
	if (position.x-radius <= 0) speedX = (rand() + 1) % 20;

	if (position.y+radius >= 600) speedY = -((rand() + 1) % 20);
	if (position.y-radius <= 0)	speedY = (rand() + 1) % 20;

	position.x += speedX;
	position.y += speedY;
}
