#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int i, j, k, counter = 0, color, loop;
	for (i = 1; i <=6; i++)
	{
		for (j = 1; j <=6; j++)
		{
			if (j > i)
			{
				for (k = 1; k <= 6; k++)
				{
					if (k > j)
					{
						counter++;

					for (loop = 1; loop <= 3; loop++)
	{
		switch (loop)
		{
		case 1:color = i; break;
		case 2:color = j; break;
		case 3:color = k; break;
		}
		switch (color) {
		case 1:cout << setw(15) << "red"; break;
		case 2:cout << setw(15) << "yellow"; break;
		case 3:cout << setw(15) << "blue"; break;
		case 4:cout << setw(15) << "white"; break;
		case 5:cout << setw(15) << "black"; break;
		case 6:cout << setw(15) << "green"; break;
		}
	}
	cout<<endl;}
				}
			}
		}
	}

	cout << "总共有：" << counter << "种取法";
	return 0;
}
