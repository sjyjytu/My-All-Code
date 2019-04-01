#include "Line.h"
Line::Line(Point A , Point B ):pa(A),pb(B)
{
	if (B.x != A.x)
	{
		k = (B.y - A.y) / (B.x - A.x);
		b = A.y - k * A.x;
		special = 0;
	}
	else
	{
		special = 1;
		k = A.x;
	}
	
}

Line::~Line()
{
}

bool Line::Point_up_side(Point a)
{
	if (!special)
	{
		if (a.y > (k*a.x + b))
		{
			return true;
		}
		return false;
	}
	else
	{
		if (a.x > k)
		{
			return true;
		}
		return false;
	}
	
}
