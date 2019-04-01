#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>
using namespace std;


void bfs(vector<int> number,int n,int target,bool &found)
{
	if (found == 1)
		return;
	if (n == 1)
	{
		if (number[0] == target)
			found = 1;
		return;
	}
	long long mul = 1, sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (number[i] != 0)
		{
			mul *= number[i];
			sum += number[i];
		}
	}
	if (mul < target&&sum < target)
		return;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int a = number[i];
			int b = number[j];
			vector<int> tmpVec(number);
			tmpVec.erase(tmpVec.begin() + i);
			tmpVec.erase(tmpVec.begin() + j - 1);
			int result = 0;
			int tmpN = n - 1;
			for (int k = 0; k < 5; k++)
			{
				if (found)
					return;
				switch (k)
				{
				case 0:
					result = a + b;
					tmpVec.push_back(result);
					bfs(tmpVec, tmpN, target, found);
					tmpVec.pop_back();
					break;
				case 1:
					result = (a > b)?(a-b):(b-a);
					tmpVec.push_back(result);
					bfs(tmpVec, tmpN, target, found);
					tmpVec.pop_back();
					break;
				case 2:
					result = a * b;
					tmpVec.push_back(result);
					bfs(tmpVec, tmpN, target, found);
					tmpVec.pop_back();
					break;
				case 3:
					if (b != 0)
					{
						result = a / b;
						tmpVec.push_back(result);
						bfs(tmpVec, tmpN, target, found);
						tmpVec.pop_back();
					}
					break;
				case 4:
					if (a != 0)
					{
						result = b / a;
						tmpVec.push_back(result);
						bfs(tmpVec, tmpN, target, found);
						tmpVec.pop_back();
					}
					break;
				default:
					break;
				}
			}
				
		}
	}
}
int main()
{
	while (true)
	{
		cout << endl;
		clock_t start, finish;
		srand((unsigned)time(NULL));
		int n = 9, target = 0;
		//cout << "input n,target,number[i]:";
		//cin >> n >> target;
		cout << "input n:"<<n<<endl;
		//cin >> n;
		target = rand() % 1000;
		cout << "target:" << target << endl;
		vector <int> number;

		for (int i = 0; i < n; i++)
		{
			//int tmp = 0;
			//cin >> tmp;
			
			int tmp = rand() % 100;
			cout << tmp << "  ";

			number.push_back(tmp);
		}
		cout << endl;
		bool found = 0;
		start = clock();
		bfs(number, n, target, found);
		finish = clock();
		if (found)
		{
			cout << "True" << endl;
		}
		else
		{
			cout << "False" << endl;
		}
		cout << "time:" << double(finish - start) / 1000 << "s" << endl;
		Sleep(2000);
	}
	
	
	
	system("pause");
	return 0;
}