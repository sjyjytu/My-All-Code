#include <iostream>

using namespace std;
void dy(int);
int main()
{
   int n;
   cout<<"������һ����������"<<endl;
   cin>>n;
   dy(n);
   return 0;
}
void dy(int n)
{
    if (n<10) cout<<static_cast<char>(n+'0');
    else {dy(n/10);cout<<static_cast<char>(n%10+'0');}
}
