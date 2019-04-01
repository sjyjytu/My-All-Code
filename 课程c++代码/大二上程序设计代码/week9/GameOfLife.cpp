#include <iostream>
#include <random>
#include<Windows.h>
using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;
	bool **State = new bool*[m];
	bool **NewState = new bool *[m];
	for (int i = 0; i < m; i++)
	{
		State[i] = new bool[n];
		NewState[i] = new bool[n];
	}
		
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			//cin >> State[i][j];
			State[i][j] = rand() > 20000;
	while (true)
	{
		system("cls");
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				int livecount = 0;
				for (int k = -1; k<2; k++)
					for (int l = -1; l < 2; l++)
					{
						if (k || l)
						{
							/*if (i + k >= 0 && i + k < m&&j + l >= 0 && j + l < n)
								livecount += State[i + k][j + l];*/
							livecount += State[(i + k + m) % m][(j + l + n) % n];
						}
					}
				if (State[i][j] == 0)
				{
					if (livecount == 3)
						NewState[i][j] = 1;
					else
						NewState[i][j] = 0;
				}
				else
				{
					if (livecount == 2 || livecount == 3)
						NewState[i][j] = 1;
					else
						NewState[i][j] = 0;
				}
			}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (NewState[i][j])
					cout << "*" << "  ";
				else
					cout << /*NewState[i][j] <<*/ "   ";
				State[i][j] = NewState[i][j];
			}
			cout << endl;
		}
		//system("pause");
		//Sleep(0.001);
	}
	
	return 0;
}