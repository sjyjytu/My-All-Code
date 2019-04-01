#include <vector>
#include <iostream>

using namespace std;
int main()
{
	int i = 0;
	while (i < 20)
	{
		i++;
		switch (i%3)
		{
		case 0:
			if (i < 10)
				continue;
			else
			{
				cout << "wow!"<<endl;
			}
			break;
		case 1:
			cout << i << endl;
			break;
		default:
			break;
		}
	}
	system("pause");
}