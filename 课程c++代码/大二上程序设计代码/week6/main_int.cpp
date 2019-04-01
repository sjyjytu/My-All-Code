#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

//int Count;
void bfs(vector<double> number,int n,int target,bool &found)
{
	if (found == 1)
		return;
	if (n == 1)
	{
		if (number[0] == target)
			found = 1;
		return;
	}
	//if (Count > 30000)
	//	return;
	long double mul = 1, sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (number[i] > 0)
		{
			sum += number[i];
		}
		if (number[i] > 1)
		{
			mul *= number[i];
		}
	}
	if (mul < target&&sum < target)
		return;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			double a = number[i];
			double b = number[j];
			vector<double> tmpVec(number);
			tmpVec.erase(tmpVec.begin() + i);
			tmpVec.erase(tmpVec.begin() + j - 1);
			double result = 0;
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
	//Count++;
}
int main()
{
	//Count = 0;
	//cout << endl;
	//clock_t start, finish;
	//srand((unsigned)time(NULL));
	int n = 9, target = 0;
	cout << "input n,target,number[i]:";
	cin >> n >> target;
	//cout << "input n:"<<n<<endl;
	//cin >> n;
	//target = rand() % 1000;
	//cout << "target:" << target << endl;
	vector<double> number;

	for (int i = 0; i < n; i++)
	{
		double tmp = 0;
		cin >> tmp;
			
		//int tmp = rand() % 100;
		//cout << tmp << "  ";

		number.push_back(tmp);
	}
	cout << endl;
	bool found = 0;
	//start = clock();
	bfs(number, n, target, found);
	//finish = clock();
	if (found)
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
	}
	//cout << "time:" << double(finish - start) / 1000 << "s" << endl;
	
	system("pause");
	return 0;
}