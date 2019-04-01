#include <iostream>
#include <vector>
#include <stdio.h>
#include "Point.h"
#include <string>
using namespace std;

int x_mul(Point a, Point b)
{
	return  a.x*b.y - a.y*b.x;
}
int p_mul(Point a, Point b)
{
	return a.x*b.x + a.y*b.y;
}
bool Point_in(Point A, Point B, Point C, Point P)
{
	//借用Point类来表示向量
	Point AB = B - A;
	Point BC = C - B;
	Point CA = A - C;
	Point AP = P - A;
	Point BP = P - B;
	Point CP = P - C;
	int a = x_mul(AB, AP);
	int b = x_mul(BC, BP);
	int c = x_mul(CA, CP);
	if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
		return true;
	return false;
}
/*same side: y = y2-y1/x2-x1 *(x-x1) + y1 */
void dintotri(vector<Point> pvec,vector<vector<Point> > &output)
{
	if (pvec.size() == 3)
		return;
	pvec.insert(pvec.begin(), *(pvec.end() - 1));
	pvec.push_back(*pvec.begin());
	
	/*for (vector<Point>::iterator it = pvec.begin(); it != pvec.end(); it++)
	{
		
		cout << (*it).x << "," << (*it).y << "  ";
		
		
	}
	cout << endl;
	char x;
	cin >> x;*/
	for (vector<Point>::iterator it = pvec.begin() + 1; it != pvec.end() - 1; it++)
	{
		bool ok = 1;
		for (vector<Point>::iterator j = pvec.begin() + 1; j != pvec.end() - 1; j++)
		{
			if (*j != *(it - 1) && *j != *(it) && *j != *(it + 1))
			{
				if (Point_in(*(it - 1), *it, *(it + 1), *j)|| x_mul(*it - *(it - 1), *(it + 1) - *it)>0)
				{
					ok = 0;
					break;
				}
			}
			else
				continue;

		}
		if (ok)
		{
			if (x_mul(*it - *(it - 1), *(it + 1) - *it) != 0)
			{
				vector<Point> tmp;
				tmp.push_back(*(it - 1));
				tmp.push_back(*(it));
				tmp.push_back(*(it + 1));
				output.push_back(tmp);
			}
			
			pvec.erase(it, it + 1);
			pvec.pop_back();
			pvec.erase(pvec.begin(), pvec.begin() + 1);
			break;
		}
	}
	dintotri(pvec,output);
}
int main()
{
	vector<Point> pvec;
	int x = 0, y = 0;
	char c = ',';
	while (cin>>x>>c>>y)
	{
		pvec.push_back(Point(x, y));
		
	}
	/*for (vector<Point>::iterator it = pvec.begin(); it != pvec.end(); it++)
	{

		cout << (*it).x << "," << (*it).y << "  ";


	}
	cout << endl;*/
	

	vector<vector<Point> > output;
	dintotri(pvec, output);

	for (vector<vector<Point> >::iterator it = output.begin(); it != output.end(); it++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << (*it)[i].x << "," << (*it)[i].y<<"  ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
