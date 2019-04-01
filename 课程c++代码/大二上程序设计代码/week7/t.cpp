#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int f(const int& a)
{
	cout << "oh!" << endl;
	return a + 2;
}
int main()
{
	int a = 1;
	int c = f(a);
	cout << c;
	system("pause");
	return 0;
}