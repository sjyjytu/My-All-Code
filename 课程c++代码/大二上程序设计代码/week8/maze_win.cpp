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

class Point
{
    public:
        int X;
        int Y;
    
    Point (){

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
        } else 
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
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
	for (int i = 0; i < maze[0].size(); i++)
		cout << setw(2) << i;
	cout << endl;
    for(int i = 0; i < maze.size(); i++)
    {
        for(int j = 0; j < maze[i].size(); j++)
        {
            if (maze[i][j] == 1)
            {
                SetConsoleTextAttribute(hOut, GREEN);
                cout<<"  ";
            }
            else if(maze[i][j] == 2)
            {
                SetConsoleTextAttribute(hOut, WHITE);
                cout<<"  ";
            }
            else if(maze[i][j] == 3)
            {
                SetConsoleTextAttribute(hOut, RED);
                cout<<"  ";
            }
            else if(maze[i][j] == 5)
            {
                SetConsoleTextAttribute(hOut, PURPLE);
                cout<<"  ";
            }
            else
            {
                SetConsoleTextAttribute(hOut, YELLOW);
                cout<<"  ";
            }
        }
        cout<<endl;
    }
    cout << endl;
    SetConsoleTextAttribute(hOut, WHITE_END);
}

bool outEdge(Point p, vector<vector<int> > maze)
{
	//判断是否出界
	if (p.X < 0 || p.X >= maze.size() || p.Y < 0 || p.Y >= maze[0].size())
		return true;
	else
	{
		return false;
	}
}
bool solve1(vector<vector<int> > &maze, Point start, Point end)
{
	//深搜，够快
	int x = start.X;
	int y = start.Y;
    //1绿色：路障；  0黄色：未开发过的路；  5紫色：当前路径  3红色：死点，没前途
	if (start == end)
	{
		maze[x][y] = 5;
		return true;
	}
	if (outEdge(start,maze)|| maze[x][y] == 1)
		return false;
	int state = maze[x][y];  //当前格子的状态
	if (state == 0)
	{
		maze[x][y] = 5;
		//遍历四周
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i == 0 && j == 0)
					continue;
				if (solve1(maze, Point(x + i, y + j), end))
					return true;  //找到了 返回真
			}
		}
		//向四周探索都没有路，说明这个点是死点，标记它
		maze[x][y] = 3;
		return false;
	}
	if (state == 5)
		return false;  //避免重复
	if (state == 3)  //遇到了死点，应该撤退，没这么简单
		return false;
	else
		return false;
}
bool solve(vector<vector<int> > &maze, queue<Point> &que, Point start,Point end, map<int, Point> &whosurfather)
{
	//广搜，能找到最短路径
	//1绿色：路障  0黄色：待开发  5紫色：路径  3红色：被走过了
	if (que.size() == 0)
		return false;  //没有路
	Point curPoint = que.front();
	que.pop();
	if (curPoint == end)
	{
		//找爸爸
		Point father = whosurfather[curPoint.X*100+curPoint.Y];
		while (father != start)
		{
			maze[curPoint.X][curPoint.Y] = 5;
			curPoint = father;
			father = whosurfather[curPoint.X * 100 + curPoint.Y];
		}
		maze[curPoint.X][curPoint.Y] = 5;
		maze[start.X][start.Y] = 2;
		return true;
	}
		

	int x = curPoint.X;
	int y = curPoint.Y;
	
	if (outEdge(curPoint, maze) || maze[x][y] == 1 || maze[x][y] == 3)
		return false;
	
	if (maze[x][y] == 0)
	{
		maze[x][y] = 3;
		//遍历四周
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i == 0 && j == 0)
					continue;
				Point tmp(x + i, y + j);
				if (!outEdge(tmp, maze))
				{
					que.push(tmp);
					whosurfather.insert(make_pair(tmp.X*100+tmp.Y, curPoint));
				}
			}
		}
	}
	return false;
}
int main()
{
    while(true){
        int width;
        int height;

        cout<<"Please input the width:";
        cin>>width;
        cout<<"Please input the height:";
        cin>>height;

        vector<vector<int> > maze = generate(width, height);
		map<int, Point> whosurfather;

        //printMaze(maze);
        int start_x=0, start_y=0, end_x=height-1, end_y=width-1;
        /*cout << "Please input the start point:";
        cin >> start_x >> start_y;
        cout << "Please input the end point:";
        cin >> end_x >> end_y;*/
		while (maze[start_x][start_y]!=0)
		{
			start_x++;
			start_y++;
		}
		while (maze[end_x][end_y] != 0)
		{
			end_x--;
			end_y--;
		}
		cout << "start point:" << start_x << "  " << start_y << endl;
		cout << "end point:" << end_x << "  " << end_y << endl;
        Point start(start_x, start_y);
        Point end(end_x, end_y);
		queue<Point> que;
		que.push(start);
		bool find = 0;
		clock_t go = clock();
		while (que.size() != 0 && !find)
			find = solve(maze, que, start, end, whosurfather);
		//solve1(maze, start, end);
		clock_t finish = clock();
		cout << "times:  " << finish - go << "  ms" << endl;
        //printMaze(maze);

        system("pause");
    }
    return 0;
}
