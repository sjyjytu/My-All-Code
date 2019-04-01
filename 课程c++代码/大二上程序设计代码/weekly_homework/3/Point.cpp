#include "Point.h"
Point::Point(int px, int py)
{
	x = px;
	y = py;
}

Point::~Point()
{
}

Point Point::operator-(const Point &p)
{
	Point point;
	point.x = this->x - p.x;
	point.y = this->y - p.y;
	return point;
}

bool Point::operator!=(const Point &p)
{
	if (this->x==p.x&&this->y==p.y)
		return false;
	return true;
}

