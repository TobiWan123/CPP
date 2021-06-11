#include "Collider.h"
#include <iostream>



bool Collider::collideEllipse(Circle *circle1, Circle *circle2) {
	
	radiuses = circle1->radius + circle2->radius;

	Point c1 = circle1->getPosition();
	Point c2 = circle2->getPosition();

	// distance between 2 points -> wurzel((x2-x1)^2+(y2-y1)^2)
	distance = sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));

	return distance - 5 < radiuses;
}

// check collison for each axis of the polygons
bool Collider::collidePolygon(Poly* poly1, Poly* poly2) {

	Point point1 = poly1->getPosition();
	Point point2 = poly2->getPosition();

	Point diff;
	diff.x = point1.x - point2.x; 
	diff.y = point1.y - point2.y;

	Point* obj1Points = poly1->getRotatedPoints();
	int obj1PointsN = poly1->getNumberOfPoints();
	Point* obj2Points = poly2->getRotatedPoints();
	int obj2PointsN = poly2->getNumberOfPoints();


	// distance between 2 points -> wurzel((x2-x1)^2+(y2-y1)^2)
	double distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	double radiuses = poly1->radius + poly2->radius;

	if (distance < radiuses) {

		// for every axis of obj1
		for (int i = 0; i < obj1PointsN; i++) {

			int j = i + 1;
			if (j == obj1PointsN) j = 0;

			Point lineVector;
			lineVector.x = obj1Points[i].y - obj1Points[i].y;
			lineVector.y = obj1Points[i].x - obj1Points[j].x;

			if (collideOnAxis(lineVector, obj1Points, obj1PointsN, obj2Points, obj2PointsN, diff)) {
				return true;;
			}
		}

		// for every axis f obj2
		for (int i = 0; i < obj2PointsN; i++) {

			int j = i + 1;
			if (j == obj2PointsN) j = 0;

			Point lineVector;
			lineVector.x = obj2Points[i].y - obj2Points[i].y;
			lineVector.y = obj2Points[i].x - obj2Points[j].x;

			if (collideOnAxis(lineVector, obj1Points, obj1PointsN, obj2Points, obj2PointsN, diff)) {
				return true;
			}
		}

	}

	return false; 
}

// check collision for each axis with circle (projected point is center + radius)
bool Collider::collidePolyCircle(Poly* poly1, Circle* circle1){
	


	return true;
}

// calculate if there is an intercept between 2 Obj with projected points on a lineVector
// the lineVector represents one axis of one polygon in space with (x,y)
// we check if any of the points from the 2 objects overlap on the axis with thir distance the projected point travleded on the axis
// if we find one axis in the space where the points dont overlap with der min/max distance, the we have no collision
// thex axises, represented by the lineVector lay from (0,0) in any calculated direction in space
// imagine an (x,y) space with the objPoints gathered around the (0,0) coord -> obj centerpoint is (0,0)
// now lay any axis of each obj through (0,0) and calculate the distances on this axis traveled by each point from (0,0)
// if x+y of one projected point are lower than 0, the distance is negative
bool Collider::collideOnAxis(Point lineVector, Point* obj1Points, int ob1PointsN, Point* obj2Points, int ob2PointsN, Point diff) {
	
	// initialize distances of projected points on line with lowest/highest value
	double obj1Min =  DBL_MAX;
	double obj1Max = -DBL_MAX;
	double obj2Min =  DBL_MAX;
	double obj2Max = -DBL_MAX;

	// calculate the min and the max distance of obj1 on lineVector
	for (int i = 0; i < ob1PointsN; i++) {
		Point projected = getProjectedPoint(obj1Points[i], lineVector);

		double distanceOnLine = sqrt(pow(projected.x, 2) + pow(projected.y, 2));

		if (projected.x + projected.y < 0) distanceOnLine = -distanceOnLine;
		if (obj1Min > distanceOnLine) obj1Min = distanceOnLine;
		if (obj1Max < distanceOnLine) obj1Max = distanceOnLine;
	}

	for (int i = 0; i < ob2PointsN; i++) {

		// calculate adjustedPoints to translate the both polygons to the same position 
		// calculate from (0,0)
		// add deltaX and deltaY to the second object or remove it from the first!!
		Point adjustedPoint;
		adjustedPoint.x = obj2Points[i].x + diff.x;
		adjustedPoint.y = obj2Points[i].y + diff.y;

		Point projected = getProjectedPoint(adjustedPoint, lineVector);

		double distanceOnLine = sqrt(pow(projected.x, 2) + pow(projected.y, 2));

		if (projected.x + projected.y < 0) distanceOnLine = -distanceOnLine;
		if (obj2Min > distanceOnLine) obj2Min = distanceOnLine;
		if (obj2Max < distanceOnLine) obj2Max = distanceOnLine;
	}

	if (obj1Max < obj2Min || obj2Max < obj1Min) return false;

	return true;
}

bool collideOnAxis(Point lineVector, Point* obj1Points, int ob1PointsN, Point* obj2Points, double obj2Radius, Point diff) {

	return true;
}


// calculate the projection of one point on a given lineVector assuming its origin in (0,0)
// with the projection on the line we can calculate the distance each projected point takes on the lineVector
// with checking if 2 of the distances of 2 objects overlap, we know there is a collision
Point Collider::getProjectedPoint(Point p, Point lineVector) {
	Point projection;
	projection.x = ((p.x * lineVector.x + p.y * lineVector.y) / (pow(lineVector.x, 2) + pow(lineVector.y, 2))) * lineVector.x ;
	projection.y = ((p.x * lineVector.x + p.y * lineVector.y) / (pow(lineVector.x, 2) + pow(lineVector.y, 2))) * lineVector.y ;

	return projection;
}