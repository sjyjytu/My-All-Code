#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
struct circle
{
	double x;
	double y;
	double r;
	circle(double _x, double _y, double _r)
	{
		x = _x;
		y = _y;
		r = _r;
	}
};

bool in_it(vector<circle> circles, double X, double Y)
{
	for (int i = 0; i < circles.size(); i++)
	{
		if ((X - circles[i].x)*(X - circles[i].x) + (Y - circles[i].y)*(Y - circles[i].y) <= circles[i].r*circles[i].r)
			return 1;
	}
	return 0;
}
int main()
{
	ifstream file("circles.txt");
	vector<circle> circles;
	while (!file.eof())
	{
		double _x;
		double _y;
		double _r;		
		file >> _x >> _y >> _r;
		circle _circle(_x,_y,_r);
		circles.push_back(_circle);
	}
	clock_t start = clock();
	//get border
	double lw = circles[0].x - circles[0].r,
		rw = circles[0].x + circles[0].r,
		tw = circles[0].y + circles[0].r,
		bw = circles[0].y - circles[0].r;
	for (int i = 1; i < circles.size(); i++)
	{
		double l = circles[i].x - circles[i].r;
		double r = circles[i].x + circles[i].r;
		double t = circles[i].y + circles[i].r;
		double b = circles[i].y - circles[i].r;
		if (l < lw)
			lw = l;
		if (r > rw)
			rw = r;
		if (t > tw)
			tw = t;
		if (b < bw)
			bw = b;
	}
	double precision = 0;
	cout << "precision:";
	cin >> precision;
	//begin at left buttom
	double area = 0;
	for (double X = lw;X<rw;X+=precision)
	{
		for (double Y = bw; Y < tw; Y += precision)
		{
			for (int i = 0; i < circles.size(); i++)
			{
				if ((X - circles[i].x)*(X - circles[i].x) + (Y - circles[i].y)*(Y - circles[i].y) <= circles[i].r*circles[i].r)
				{
					area += precision * precision;
					break;
				}
			}
		}
	}
	clock_t finish = clock();

	cout.precision(10);
	cout << "area:" << area << endl;
	cout << "time:" << (finish - start) << "ms" << endl;
	system("pause");
	return 0;
}