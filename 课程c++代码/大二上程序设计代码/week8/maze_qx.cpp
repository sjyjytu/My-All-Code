//#include "pch.h"

#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <windows.h>
#include <cmath>
#include <set>
#include <map>
#include <stack>

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

    Point(int y, int x)
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

    bool operator < (const Point& point) const
    {
        return this->Y * 100000 + this->X < point.Y * 100000 + point.X;
    }
};

vector<vector<int> > generate(int width, int height)
{
    mt19937 rng;
    rng.seed(time(nullptr));
    //rng.seed(1);

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
    /*
    for (int i = 0; i < maze.size(); i++)
    {
        for (int k = 0; k < maze.size(); k++)
        {
            if (maze[i][k] == 2 || maze[i][k] == 5)
            {
                cout << '(' << i << ',' << k << ')' << endl;
            }
        }
    }*/
}

int distance(Point A, Point B)
{
    int distance = 0;
    int D_X = abs(A.X - B.X), D_Y = abs(A.Y - B.Y);
    if (D_X > D_Y)
    {
        distance = 14 * D_Y + 10 * (D_X - D_Y);
    }
    else
    {
        distance = 14 * D_X + 10 * (D_Y - D_X);
    }
    return distance;
}

class Property {
public:
    int H_cost;
    int G_cost;
    int F_cost;
    Point location;
    Point fatherPoint;
    Property() {}

    Property(const Point& start,const Point& end)
    {
        fatherPoint = Point(-1, -1);
        location = start;
        H_cost = distance(start, end);
        G_cost = 0;
        F_cost =  H_cost + G_cost;
    }

    Property(const Point& givenLocation,const Property& givenFatherPointProperty,const Point& end)
    {
        fatherPoint = givenFatherPointProperty.location;
        location = givenLocation;
        H_cost = distance(location, end);
        G_cost = distance(givenFatherPointProperty.location, location) + givenFatherPointProperty.G_cost;
        F_cost =  H_cost + 0*G_cost;
    }

    ~Property() {}

    Property& operator=(const Property& A)
    {
        if (this == &A)
        {
            return *this;
        }

        H_cost = A.H_cost;
        F_cost = A.F_cost;
        G_cost = A.G_cost;
        location = A.location;
        fatherPoint = A.fatherPoint;

        return *this;
    }

    bool operator< (const Property& A) const
    {
        if (F_cost < A.F_cost)
        {
            return true;
        }
        else if (F_cost == A.F_cost)
        {
            if (H_cost < A.H_cost)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
};

bool solve(vector<vector<int> > &maze,const Point& start,const Point& end)
{
    /*
    0 黄色 墙 
    1 绿色 可以走
    2 蓝色 起点，路径
    3 红色 搜寻过的点
    5 紫色 终点
    */

    /*设定起点和终点颜色*/
    maze[start.Y][start.X] = 2;
    maze[end.Y][end.X] = 5;

    /*开始检索*/
    set<Property> searchingPoints;
    map<Point, Property> searchedPoints;//第一个位置放点的值，第二个位置放点的属性
    searchingPoints.insert(Property(start, end));
    //set<Point> searchedPoints;

    bool findWay = false;
    while (!findWay)
    {
        if (searchingPoints.size() == 0)
        {
            return false;
        }
        /*将min放入searchedPoints*同时从searchingPoints中剔除*/
        Property min = *searchingPoints.begin();
        searchingPoints.erase(searchingPoints.begin());
        if (searchedPoints.find(min.location) != searchedPoints.end())
        {
            continue;
        }
        //cout<< "min: " << min.location.Y << ' ' << min.location.X << endl;
        searchedPoints.insert(make_pair(min.location, min));
        //searchedPoints.insert(min.location);
        
        
        /*对这个值最小的点周围的点进行处理,将周围的点放入searchingPoints*/
        for (int i = -1; i <= 1; i++)
        {
            for (int k = -1; k <= 1; k++)
            {
                if (i == 0 && k == 0)
                {
                    continue;
                }
                /*检查越界*/
                if ((min.location.X + i < 0)
                    || (min.location.X + i > maze[0].size() - 1)
                    || (min.location.Y + k < 0)
                    || (min.location.Y + k > maze.size() - 1))
                {
                    continue;
                }

                if (maze[min.location.Y + k][min.location.X + i] == 0)
                {
                    continue;
                }

                if (searchedPoints.find(Point(min.location.Y + k, min.location.X + i)) != searchedPoints.end())
                {
                    continue;
                }
                maze[min.location.Y + k][min.location.X + i] = 3;

                Property tempProperty(Property(Point(min.location.Y + k, min.location.X + i), min, end));
                //cout << tempProperty.location.Y << ' ' << tempProperty.location.X << endl;
                if (tempProperty.location == end)
                {
                    searchedPoints.insert(make_pair(tempProperty.location, tempProperty));
                    //searchedPoints.insert(tempProperty.location);
                    findWay = true;
                }
                /*
                bool if_change = false;
                auto it = searchedPoints.find(tempProperty.location);
                if (it != searchedPoints.end())
                {
                    if (it->second.G_cost > tempProperty.G_cost)
                    {
                        searchingPoints.erase(it);
                        searchingPoints.insert(tempProperty);
                        if_change = true;
                        break;
                    }
                }
                
                if (!if_change)
                {
                    searchingPoints.insert(tempProperty);
                }*/
                searchingPoints.insert(tempProperty);
            }
        }
    }
    
    
    Property tempPoint = searchedPoints[end];
    
    while (true)
    {
        tempPoint = searchedPoints[tempPoint.fatherPoint];
        maze[tempPoint.location.Y][tempPoint.location.X] = 2;
        if (tempPoint.fatherPoint == start)
        {
            break;
        }
    }
    maze[start.Y][start.X] = 2; 
    maze[end.Y][end.X] = 5; 

    return true;
}

int main()
{
    while (true) {
        int width;
        int height;

        cout << "Please input the width:";
        cin >> width;
        cout << "Please input the height:";
        cin >> height;

        double total_time = 0;
        for (int i = 0; i < 10; i++)
        {
            vector<vector<int> > maze = generate(width, height);

            

            int start_x = 0, start_y = 0, end_x = width - 1, end_y = height - 1;
            //start_x = rand() % width;
            //start_y = rand() % height;
            //end_x = rand() % width;
            //end_y = rand() % height;
            
            while (maze[start_y][start_x] == 0 || maze[end_y][end_x] == 0 )//||(distance(start,end)<=6*(width+height)))
            {
                start_x = rand() % width;
                //start_y = rand() % height;
                end_x = rand() % width;
                //end_y = rand() % height;
            }
            maze[start_y][start_x] = 2;
            maze[end_y][end_x] = 5;
            cout << start_y << ' ' << start_x << ' ' << end_y << ' ' << end_x << endl;
            //printMaze(maze);
            /*
            cout << "Please input the start point:";
            cin >> start_y >> start_x;
            cout << "Please input the end point:";
            cin >> end_y >> end_x;*/
            
            Point start(start_y, start_x);
            Point end(end_y, end_x);

            bool answer;

            clock_t begin_time, end_time;

            begin_time = clock();

            answer = solve(maze, start, end);

            end_time = clock();


            if (answer)
            {
                //printMaze(maze);
                //total_time += double(end_time - begin_time);
                cout << "Find!!" << endl;
            }
            else
            {
                cout << "there is no answer at " << i << " time" << endl;
                
            }
            total_time += double(end_time - begin_time);
            cout << "Having used " << double(end_time - begin_time) / CLK_TCK << " s" << endl;
            //cout << start_y << ' ' << start_x << ' ' << end_y << ' ' << end_x << endl;
            system("pause");
        }
        cout << "average_time:" << total_time / CLK_TCK / 10 << " s" << endl;
    }
    return 0;
}
