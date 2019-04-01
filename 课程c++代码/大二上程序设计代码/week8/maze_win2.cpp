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

bool solve1(vector<vector<int> > &maze, int start_X,int start_Y, int end_X,int end_Y, vector<int> direction, int &count)
{
	count++;
	/*if (count % 100 == 0)
		cout << count << "layers..." << endl;*/
	//深搜
	int x = start_X;
	int y = start_Y;
	if (start_X == end_X&&start_Y==end_Y)
	{
		maze[x][y] = 5;
		return true;
	}
	if (x < 0 || x >= maze.size() || y < 0 || y >= maze[0].size() || maze[x][y] != 0)
		return false;

	//1绿色：路障；  0黄色：未开发过的路；  5紫色：当前路径  3红色：死点，没前途
	//int state = maze[x][y];  //当前格子的状态
	//if (state == 0)
	else
	{
		int direc_x = end_X - start_X;
		int direc_y = end_Y - start_Y;
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
		maze[x][y] = 5;
		//遍历四周
		if (solve1(maze, x + direc_x, y + direc_y, end_X,end_Y,direction,count))
			return true;  //找到了 返回真
		int convert_cur_direc = (direc_x + 1) * 10 + direc_y + 1;//将横纵坐标都+1（处理-1）
		int index = 0;
		for (auto it = direction.begin(); it != direction.end(); it++)
		{
			if (*it == convert_cur_direc)
			{
				break;
			}
			index++;
		}//找对应下标
		int cur = direction[(index + 7) % 8];//取左边一个
		if (solve1(maze, x + cur / 10 - 1, y + cur % 10 - 1, end_X,end_Y, direction,count))
			return true;  //找到了 返回真

		for (int i = 1; i < 7; i++)
		{
			int cur = direction[(index + i) % 8];//往右取
			if (solve1(maze, x + cur / 10 - 1, y + cur % 10 - 1, end_X, end_Y, direction,count))
				return true;  //找到了 返回真
		}
		//向四周探索都没有路，说明这个点是死点，标记它
		maze[x][y] = 3;
		return false;
	}
	//return false;
}
int main()
{
	while (true) {
		int width=3000;
		int height=3000;

		/*cout << "Please input the width:";
		cin >> width;
		cout << "Please input the height:";
		cin >> height;*/

		vector<vector<int> > maze = generate(width, height);
		cout << "generate finished!" << endl;

		int start_x=0, start_y=0, end_x=height-1, end_y=width-1;
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
		if (solve1(maze, start_x,start_y, end_x,end_y, direction,count))
			cout << "find!" <<"\tfor"<<count<<"times"<< endl;
		clock_t stop = clock();
		double comsume = stop - go;
		cout << "comsume:" << comsume << "ms" << endl;
		system("pause");
	}
	return 0;
}