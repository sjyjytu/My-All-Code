#include <iostream>

using namespace std;
int f(int m)//f�����ǽ׳�
{
    int n=1,j;
    for (j=1;j<=m;j++) n=n*j;
    return n;
}
int sin(double x,double y=1/1000000)
{
    double b,c=0; int i=1,d=x,g=-1;//bΪ�׳ˣ�
    for (int k=1;b<(d/y);k++) {g=-1*g; b=f(i); i+=2; c=c+g*d/b;d=d*x*x; }

    return c;
}
int main()
{
    double l,h;
    cout << "������x��ֵ��" << endl;
    cin>>l;
    h=sin(l);
    cout<<"sinx��ֵΪ��"<<h;
    return 0;
}
