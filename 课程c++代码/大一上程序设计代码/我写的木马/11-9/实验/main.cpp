#include <iostream>
#include <string>
using namespace std;
int main()
{
     string x="aaabbbcccdd1232ddd";
     string y="1132";
     int p=x.find(y,0);  // pΪ�ҵ���λ��,-1Ϊδ�ҵ�
      x.erase(p,y.length());
     cout << x << endl;
return 0;}





#include <iostream>
 #include <string>
 using namespace std;
 int main()
 {
string str = "afdsdfs_hello_sdfas#@!";
string str1 = "hello";

string::size_type idx = str.find( str1 );

if ( idx != string::npos )
{
cout << "�ַ������С�<< str1 << "\n";
}
else
{
cout << "�ַ���û��" << str1 << "\n";
}
 }
