#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include<string>
class Line
{
public:
	Line(Point A = Point(0, 0), Point B = Point(0, 0));
	~Line();
	bool Point_up_side(Point);
	Point pa;
	Point pb;
private:
	double k = 0;
	double b = 0;
	bool special;
};
#endif // !LINE_H

