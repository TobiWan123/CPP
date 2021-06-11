#pragma once
#include "Circle.h"
#include "Point.h"
#include "Polygon.h"

class Collider {
private:
	float distance, radiuses;
public:
	bool collideEllipse(Circle *circle1, Circle *circle2);
	bool collidePolygon(Poly* poly1, Poly* poly2);
	bool collidePolyCircle(Poly* poly1, Circle* circle1);
	bool collideOnAxis(Point lineVector, Point* obj1Points, int ob1PointsN, Point* obj2Points, int ob2PointsN, Point diff);
	bool collideOnAxis(Point lineVector, Point* obj1Points, int ob1PointsN, Point* obj2Points, double obj2Radius, Point diff);

	Point getProjectedPoint(Point p, Point lineVector);
};

