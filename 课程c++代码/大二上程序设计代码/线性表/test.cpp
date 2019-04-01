#include <iostream>
#include "ClassTemplate.h"
using std::cout;
using std::endl;

void main()
{
	myClass<int, int> class1(3, 5);
	class1.show();

	myClass<int, char> class2(3, 'a');
	class2.show();

	myClass<double, int> class3(2.9, 10);
	class3.show();

	system("PAUSE");
}