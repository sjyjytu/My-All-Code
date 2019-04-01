#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <map>
#include <vector>
#include <ctime>


using namespace std;
int main()
{
	ifstream ifs("test.txt"); // 改成你要打开的文件
	string str = "";
	char c[2];
	char *a(c);
	
	/*while (!ifs.eof())
	{
		c[0]=ifs.get();
		c[1] = ifs.get();
		cout << c[0] << c[1]<<endl;
		str =str+ c[0]+c[1];
	}
	cout << "size:" << str.size();
	cout << "str:" << str;*/
	system("pause");
	return 0;
}