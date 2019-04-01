/*素数的距离 (必答题)

问题描述：
给定两个正整数M、N，其中1 <= M < N <= 2^64 - 1，请输出M与N之间（包含M与N）的两个相邻素数的距离的最大值，其中M与N的差值不超过1000000，当M与N之间无相邻素数时输出为零。

Sample:

Input: 2 17

Output: 4

（2与17之间的素数为2、3、5、7、11、13、17，距离最大的为13与17，因此输出为4）

Input: 3 56

Output: 6*/

/*#include <iostream>
#include <math.h>
using namespace std;
bool isPrime(unsigned long long n)
{
	if (n == 1)
	{
		return false;
	}
	if (n == 2)
	{
		return true;
	}
	else if (n % 2 == 0)
	{
		return false;
	}
	for (int i = 3; i*i <= n; i += 2)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
int main()
{
	unsigned long long m = 0, n = 0, pre = 0, maxlen = 0;
	bool havefindfirst = 0;
	//cin >> m >> n;
	m = 1<<31 - 1;
	n = 1 << 31;
	cout << m << "  " << n << endl;
	cout << ULLONG_MAX << endl;
	cout << ULONG_MAX << endl;
	unsigned long long i = 0;
	if (m % 2 == 0)
	{
		if (m == 2)
		{
			havefindfirst = 1;
			pre = 2;
			i = 3;
		}
		else
		{
			i = m + 1;
		}
	}
	else
	{
		i = m;
	}
	for (; i <= n; i += 2)
	{
		if (isPrime(i))
		{
			if (havefindfirst &&(i - pre > maxlen))
			{
				maxlen = i - pre;
			}
			pre = i;
			havefindfirst = 1;
		}
	}
	cout << maxlen;
	system("pause");
	return 0;
}*/