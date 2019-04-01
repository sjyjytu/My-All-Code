#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
int main()
{
	vector<int> cake;
	string s = "";
	while (getline(cin, s, ','))
	{
		cake.push_back(stoi(s));
	}

	vector<int>cake_size(cake);
	
	//向左边延申
	stack<pair<int,int>> left;
	left.push(make_pair(0,cake[0]));//下标和值
	for (int i = 1; i < cake.size(); i++)
	{
		if (cake[i] <= left.top().second)
		{
			while (left.top().first != 0 && left.top().second >= cake[i])
			{
				left.pop();
			}
		}
		if (left.top().first == 0&&left.top().second>=cake[i])
		{
			cake_size[i] += cake[i] * (i - left.top().first);
		}
		else
		{
			cake_size[i] += cake[i] * (i - left.top().first - 1);
		}
		left.push(make_pair(i, cake[i]));

	}

	//右边
	stack<pair<int, int>> right;
	right.push(make_pair(cake.size() - 1, cake[cake.size() - 1]));//下标和值
	for (int i = cake.size()-2; i >= 0; i--)
	{
		if (cake[i] <= right.top().second)
		{
			while (right.top().first != cake.size() - 1 && right.top().second >= cake[i])
			{
				right.pop();
			}
		}
		if (right.top().first == cake.size() - 1 && right.top().second >= cake[i])
		{
			cake_size[i] += cake[i] * (right.top().first - i);
		}
		else
		{
			cake_size[i] += cake[i] * (right.top().first - i - 1);
		}
		right.push(make_pair(i, cake[i]));
	}
	
	/*for (int i = 0; i < cake.size(); i++)
		cout << cake_size[i] << "  ";*/
	cout << *max_element(cake_size.begin(), cake_size.end());
	return 0;
}