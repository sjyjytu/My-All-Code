#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int x = 0, y = 0;
	do 
	{
		cin >> x;
		cin >> y;
	} while (abs(x) > 1000 || abs(y) > 1000);
	cout << x + y;
	return 0;
}