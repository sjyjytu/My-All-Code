#include <iostream>
#include<math.h>
using namespace std;

int f(int m)//f�����ǽ׳�
{
    int n=1,j;
    for (j=1;j<=m;j++) n=n*j;
    return n;
}
double sin(double x,double y=1/1000000)
{
    double b=0,c=0,d; int i=1,g=-1;//bΪ�׳ˣ�
    d=x;
    for (int k=1;fabs(c)<=y;k++) {g=-1*g; b=f(i); i+=2; c=c+g*d/b;d=d*x*x; }

    return c;
}
int main()
{
    double l,h;
    cout << "������x��ֵ��" << endl;
    cin>>l;
    h=sin(l,1/1000000);
    cout<<"sinx��ֵΪ��"<<h;
    return 0;
}
