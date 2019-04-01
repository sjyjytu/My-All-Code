#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <stack>
#include <map>
#include <windows.h>

#define DENSITY 60
// #define RED     4
// #define GREEN   2
// #define YELLOW  6
// #define WHITE   7
// #define PURPLE  13

#define RED     204
#define GREEN   170
#define YELLOW  238
#define WHITE   17
#define PURPLE  221

#define WHITE_END   7

using namespace std;

class Point
{
public:
	int X;
	int Y;

	Point() {

	}

	Point(int x, int y)
	{
		X = x;
		Y = y;
	}

	Point& operator= (const Point& point)
	{
		if (this == &point)
		{
			return *this;
		}

		X = point.X;
		Y = point.Y;

		return *this;
	}

	bool operator == (const Point& point) const
	{
		if (X == point.X && Y == point.Y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator != (const Point& point) const
	{
		return (X != point.X || Y != point.Y);
	}
};
	vector<vector<int> > generate(int width, int height)
	{
		mt19937 rng;
		rng.seed(time(nullptr));

		default_random_engine fixed;
		uniform_int_distribution<int> distribution(0, 99);

		vector<vector<int> > maze(height, vector<int>(width));
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				maze[i][j] = distribution(rng) < DENSITY ? 1 : 0;
			}
		}
		return maze;
	}

	void printMaze(vector<vector<int> > &maze)
	{
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		for (int i = 0; i < maze.size(); i++)
		{
			for (int j = 0; j < maze[i].size(); j++)
			{
				if (maze[i][j] == 1)
				{
					SetConsoleTextAttribute(hOut, GREEN);
					cout << "  ";
				}
				else if (maze[i][j] == 2)
				{
					SetConsoleTextAttribute(hOut, WHITE);
					cout << "  ";
				}
				else if (maze[i][j] == 3)
				{
					SetConsoleTextAttribute(hOut, RED);
					cout << "  ";
				}
				else if (maze[i][j] == 5)
				{
					SetConsoleTextAttribute(hOut, PURPLE);
					cout << "  ";
				}
				else
				{
					SetConsoleTextAttribute(hOut, YELLOW);
					cout << "  ";
				}
			}
			cout << endl;
		}
		cout << endl;
		SetConsoleTextAttribute(hOut, WHITE_END);
	}
	int h(Point cur, Point end)
	{
		return abs(cur.X - end.X) + abs(cur.Y - end.Y);
	}
	bool solve(vector<vector<int>> &maze, Point start, Point end)
	{
		vector<Point> search;
		search.push_back(start);
		bool find = 0;
		int i = 0;
		while (!find)
		{
			for (; i < search.size(); i++)
			{
				if (search[i] == end)
				{
					find = 1;
					return 1;
				}

				for (int j = 1;j>=-1;j--)
					for (int k = 1; k >= -1; k--)
					{
						if (j || k)
						{
							int x = search[i].X + j;
							int y = search[i].Y + k;
							if (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size()&& maze[x][y] == 1)
							{
								if (x == end.X&&y == end.Y)
									return 1;
								maze[x][y] = 5;
								search.push_back(Point(x, y));
							}
						}
					}
			}
			return 0;
		}
	}

	int main()
	{
		while (true)
		{
			int width;
			int height;

			cout << "Please input the width:";
			cin >> width;
			cout << "Please input the height:";
			cin >> height;

			vector<vector<int> > maze = generate(width, height);
			
			Point start(0, 0);
			Point end(height - 1, width - 1);
			while (maze[start.X][start.Y]!=1)
			{
				start.X++;
				start.Y++;
			}
			while (maze[end.X][end.Y] != 1)
			{
				end.X--;
				end.Y--;
			}
			cout << "startpoint:" << start.X << ' ' << start.Y << endl;
			cout << "endpoint:" << end.X << ' ' << end.Y << endl;
			
			if (width < 75)
				printMaze(maze);
			time_t starttime, endtime;
			starttime = clock();

			if (solve(maze, start, end))
				cout << "find!!" << endl;
			else
				cout << "no answer!!" << endl;
			endtime = clock();
			cout << "time:" << endtime - starttime << "ms" << endl;
			if (width < 75 /*&& height < 75*/)
				printMaze(maze);

			system("pause");
		}
	}