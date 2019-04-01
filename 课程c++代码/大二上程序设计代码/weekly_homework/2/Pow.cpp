/*#include <iostream>
#include <cmath>
using namespace std;

double myPow(double x, int n) {
	double tmp = x;
	int fuhao;
	fuhao = ~(n >> 31) + 1;
	n = abs(n);
	for (int i = 0; i < n - 1; i++)
	{
		x *= tmp;
	}
	if (fuhao) x = 1 / x;
	if (n == 0) x = 1;
	return x;
}
int main()
{
	
	cout<< myPow(0.00001, 2147483647);
	system("pause");
	return 0;
}*/