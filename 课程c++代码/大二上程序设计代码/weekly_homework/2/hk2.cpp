/*#include <iostream>
#include <map>

using namespace std;

int main()
{
	int num = 0;
	cin >> num;
	int tmp_input;
	map <int, int> mymap;
	map <int, int> ::iterator it;
	for (int i = 0; i < num; i++)
	{
		cin >> tmp_input;
		it = mymap.find(tmp_input);
		if (it != mymap.end())
		{
			mymap[tmp_input]++;
		}
		else
		{
			mymap.insert(pair<int, int>(tmp_input, 1));
		}
	}
	for (it = mymap.begin(); it != mymap.end(); it++)
	{
		if (it->second == 1)
		{
			cout << it->first;
			break;
		}
	}
	system("pause");
	return 0;
}*/