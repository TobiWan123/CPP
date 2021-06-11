#include "Polygon.h"

Poly::Poly(double x, double y, int ppoints) {
	position.x = x;
	position.y = y;

	polyPoints = new Point[ppoints];
	rotatedPolyPoints = new Point[ppoints];

	double angleStep = 2 * 3.141592654 / ppoints;

	pointsN = ppoints;

	for (int i = 0; i < ppoints; i++) {
		Point p;

		p.x = radius * sin(i * angleStep);
		p.y = radius * cos(i * angleStep);

		polyPoints[i] = p;
	}

	calcRotation();
}
 

void Poly::logic() {
	if (position.x + radius >= 600) speedX = -((rand() + 1) % 10);
	if (position.x - radius <= 0) speedX = (rand() + 1) % 10;

	if (position.y + radius >= 600) speedY = -((rand() + 1) % 10);
	if (position.y - radius <= 0)	speedY = (rand() + 1) % 10;

	position.x += speedX;
	position.y += speedY;

	rotation += rotationSpeed;

}

void Poly::draw(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brush) {

	calcRotation();

	for (int i = 0; i < pointsN; i++) {

		int j = i + 1;

		if (j == pointsN) j = 0;

		int calc1 = position.x + rotatedPolyPoints[i].x;
		int calc2 = position.y + rotatedPolyPoints[i].y;

		int calc3 = position.x + polyPoints[j].x;
		int calc4 = position.y + polyPoints[j].y;

		renderTarget->DrawLine(
			D2D1::Point2F(calc1,calc2),
			D2D1::Point2F(calc3, calc4),
			brush,  stroke);

		
	}
}