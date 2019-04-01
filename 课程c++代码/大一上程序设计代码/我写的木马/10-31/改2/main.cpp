#include <iostream>

using namespace std;

int f(int m)//f函数是阶乘
{
    int n=1,j;
    for (j=1;j<=m;j++) n=n*j;
    return n;
}
double sin(double x,double y=1/1000000)
{
    double b=0,c=0,d; int i=1,g=-1;//b为阶乘，
    d=x;
    for (int k=1;b<(d/y);k++) {g=-1*g; b=f(i); i+=2; c=c+g*d/b;d=d*x*x; }

    return c;
}
int main()
{
    double l,h;
    cout << "请输入x的值：" << endl;
    cin>>l;
    h=sin(l);
    cout<<"sinx的值为："<<h;
    return 0;
}
