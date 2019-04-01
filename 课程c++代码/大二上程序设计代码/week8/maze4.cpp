#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <stack>
#include <windows.h>
#include <iomanip>
#include <queue>
#include <map>

#define DENSITY 40
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

bool solve(vector<vector<int> > &maze, int start_X, int start_Y, int end_X, int end_Y, const vector<int>& direction)
{
	struct SnapShotStruct
	{
		int sx;
		int sy;
		int stage;
		int direct_x;
		int direct_y;
		int index;
	};
	bool returnVal = 0;

	stack<SnapShotStruct> snapshotStack;
	SnapShotStruct currentSnapShot;
	currentSnapShot.sx = start_X;
	currentSnapShot.sy = start_Y;
	currentSnapShot.stage = 0;
	snapshotStack.push(currentSnapShot);
	while (!snapshotStack.empty())
	{
		currentSnapShot = snapshotStack.top();
		snapshotStack.pop();
		//cout << currentSnapShot.sx << "  " << currentSnapShot.sy << "   " << currentSnapShot.stage << endl;
		if (returnVal)
			continue;
		switch (currentSnapShot.stage)
		{
		case 0:
			if (currentSnapShot.sx == end_X && currentSnapShot.sy == end_Y)
			{
				returnVal = 1;
				continue;
			}
			if (currentSnapShot.sx < 0 || currentSnapShot.sx >= maze.size() || currentSnapShot.sy < 0 || currentSnapShot.sy >= maze[0].size() || maze[currentSnapShot.sx][currentSnapShot.sy] != 0)
			{
				returnVal = 0;
				continue;
			}
			else
			{
				int direc_x = end_X - currentSnapShot.sx;
				int direc_y = end_Y - currentSnapShot.sy;
				if (direc_x > 0)
					direc_x = 1;
				else if (direc_x < 0)
					direc_x = -1;
				if (direc_y > 0)
					direc_y = 1;
				else if (direc_y < 0)
				{
					direc_y = -1;
				}
				currentSnapShot.direct_x = direc_x;
				currentSnapShot.direct_y = direc_y;
				maze[currentSnapShot.sx][currentSnapShot.sy] = 5;
				//遍历四周
				currentSnapShot.stage = 1;
				snapshotStack.push(currentSnapShot);
				SnapShotStruct newSnapShot;
				newSnapShot.stage = 0;
				newSnapShot.sx = currentSnapShot.sx + direc_x;
				newSnapShot.sy = currentSnapShot.sy + direc_y;
				snapshotStack.push(newSnapShot);
				continue;
			}
			break;
		case 1:
			if (returnVal)
			{
				returnVal = 1;
				continue;
			}
			else
			{
				int convert_cur_direc = (currentSnapShot.direct_x + 1) * 10 + currentSnapShot.direct_y + 1;
				int index = 0;
				for (auto it = direction.begin(); it != direction.end(); it++)
				{
					if (*it == convert_cur_direc)
					{
						break;
					}
					index++;
				}//找对应下标

				currentSnapShot.stage = 2;
				snapshotStack.push(currentSnapShot);
				SnapShotStruct newSnapShot[7];
				int cur = direction[(index + 7) % 8];//取左边一个
				newSnapShot[0].stage = 0;
				newSnapShot[0].sx = currentSnapShot.sx + cur / 10 - 1;
				newSnapShot[0].sy = currentSnapShot.sy + cur % 10 - 1;
				snapshotStack.push(newSnapShot[0]);
				for (int i = 1; i < 7; i++)
				{
					cur = direction[(index + i) % 8];
					newSnapShot[i].stage = 0;
					newSnapShot[i].sx = currentSnapShot.sx + cur / 10 - 1;
					newSnapShot[i].sy = currentSnapShot.sy + cur % 10 - 1;
					snapshotStack.push(newSnapShot[i]);
				}
				continue;
			}
			break;
		case 2:
			maze[currentSnapShot.sx][currentSnapShot.sy] = 3;
			returnVal = 0;
			continue;
		}
	}
	return returnVal;
}

int main()
{

	while (true) {
		int width = 10000;
		int height = 10000;

		/*cout << "Please input the width:";
		cin >> width;
		cout << "Please input the height:";
		cin >> height;*/

		vector<vector<int> > maze = generate(width, height);
		cout << "generate finished!" << endl;
		/*for (int i = 0; i<5; i++)
		{
		for (int j = 0; j < 5; j++)
		cout << maze[i][j] << "  ";
		cout << endl;
		}*/
		int start_x = 0, start_y = 0, end_x = height - 1, end_y = width - 1;
		while (maze[start_x][start_y] != 0)
		{
			start_x++;
			start_y++;
		}
		while (maze[end_x][end_y] != 0)
		{
			end_x--;
			end_y--;
		}
		cout << "start:" << start_x << "  " << start_y << endl;
		cout << "end:" << end_x << "  " << end_y << endl;
		/*for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
				cout << maze[i][j] << "  ";
			cout << endl;
		}*/
		vector<int> direction(8);
		direction[0] = 22;
		direction[1] = 21;
		direction[2] = 20;
		direction[3] = 10;
		direction[4] = 0;
		direction[5] = 1;
		direction[6] = 2;
		direction[7] = 12;
		clock_t go = clock();
		cout << "start......" << endl;
		int count = 0;
		if (solve(maze, start_x, start_y, end_x, end_y, direction))
			cout << "find!" << "\tfor" << count << "times" << endl;
		clock_t stop = clock();
		double comsume = stop - go;
		cout << "comsume:" << comsume << "ms" << endl;
		system("pause");
	}
	return 0;
}