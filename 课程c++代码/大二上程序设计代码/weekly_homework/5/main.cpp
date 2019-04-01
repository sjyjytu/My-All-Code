#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() 
{
	string input;
	cout << "Input:";
	getline(cin,input);
	string standard;
	int hang = 0;
	int lie = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (isdigit(input[i])||(input[i]>='a'&&input[i]<='z'))
		{
			standard += input[i];
		}
		else if (input[i] >= 'A'&&input[i] <= 'Z')
		{
			standard += input[i] - 'A' + 'a';
		}
	}
	if (standard.size() == 0)
		cout << "Null";
	else
	{
		int a = sqrt(standard.size());
		int b = a + 1;
		if (a*a == standard.size())  //a*a矩阵 size是完全平方数
		{
			hang = lie = a;
		}
		else if (a*b >= standard.size())  //a*b
		{
			hang = a;
			lie = b;
		}
		else  //b*b
		{
			hang = lie = b;
		}
		bool **secret = new bool *[hang];
		for (int i = 0; i < hang; i++)
		{
			secret[i] = new bool[lie];
		}
		for (int i = 0; i < hang; i++)
		{
			for (int j = 0; j < lie; j++)
			{
				if ((i*lie + j) <= standard.size() - 1)
					secret[i][j] = 1;
				else
					secret[i][j] = 0;
			}
		}
		for (int j = 0; j < lie; j++)
		{
			for (int i = 0; i < hang; i++)
			{
				if (secret[i][j])
					cout << standard[i*lie + j];
			}
			cout << ' ';
		}
	}
	return 0;
}