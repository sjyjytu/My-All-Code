#include <iostream>

using namespace std;

int main()
{
    double x,pay;
    int y;
    cout << "�����빺��Ǯ��" << endl;
    cin>>x;
    y=x/1000;
   switch(y){
   case 0:
        pay=x;break;
   case 1:pay=0.9*x;break;
   case 2:pay=0.5*x;break;
   default:pay=0.1*x;
   }
    cout<<"ʵ����Ǯ��"<<pay<<endl;
    return 0;
}
