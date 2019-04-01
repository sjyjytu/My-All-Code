#ifndef Point_H
#define Point_H

class Point
{
public:
	Point(int px = 0, int py = 0);
	~Point();
	int x;
	int y;
	Point operator-(const Point&);
	bool operator!=(const Point&);
	
private:

};
#endif // !Point_H

