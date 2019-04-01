#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
void selectPrime(ll a, ll b, bool *Prime)
{
	//Prime = new bool[b - a + 1];
	bool smallPrime[1 << 17];
	for (ll i = 0; i < b - a + 1; i++)
	{
		Prime[i] = 1;
	}
	for (ll i = 0; i*i <= b; i++)
	{
		smallPrime[i] = 1;
	}
	for (ll i = 2; i*i <= b; i++)
	{
		if (smallPrime[i])
		{
			for (ll j = 2 * i; j * j <= b; j += i)
			{
				smallPrime[j] = 0;
			}
			for (ll j = max(2LL, (a + i - 1) / i)*i; j <= b; j += i)
			{
				Prime[j-a] = 0;
			}
		}
	}
}
int main()
{
	ll m, n;
	cin >> m >> n;
	if (m == 1)
		m = 2;
	bool *result;
	result = new bool[10000000];
	selectPrime(m, n, result);
	ll maxlen = 0;
	ll prev = 0;
	bool findFirst = 0;
	for (ll i = 0; i < n - m + 1; i++)
	{
		if (result[i])
		{
			if (findFirst)
			{
				maxlen = i - prev > maxlen ? i - prev : maxlen;
				prev = i;
			}
			else
			{
				prev = i;
				findFirst = 1;
			}
		}
	}
	cout << maxlen;
	system("pause");
	delete result;
	return 0;
}