#include "ObjectBase.h"

void ObjectBase::logic() {};

void ObjectBase::logic(double elapsedTIme) {};

void ObjectBase::draw(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brush) {};

Point ObjectBase::getPosition() {
	return position;
}

void ObjectBase::calcRotation() {
	if (oldRotation != rotation) {

		for (int i = 0; i < pointsN; i++) {
			Point p;

			p.x = polyPoints[i].x * sin(rotation) - polyPoints[i].y * cos(rotation);
			p.y = polyPoints[i].x * cos(rotation) + polyPoints[i].y * sin(rotation);

			rotatedPolyPoints[i] = p;
		}

		oldRotation = rotation;
	}
}

Point* ObjectBase::getRotatedPoints() { return rotatedPolyPoints; }

int ObjectBase::getNumberOfPoints() { return pointsN; }