#include <iostream>
#include <string>
#include "Matrix.h"
using namespace std;

int main() {
	try
	{
		vector<int> values(8,1);
		Matrix A(2, 4, values);
		Matrix B(2, 4, values);
		Matrix C = Matrix();;
		//C.Print();
	}
	catch (string &e)
	{
		cout << e << endl;
	}
	system("pause");
	return 0;
}
