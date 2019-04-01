#include <iostream>

using namespace std;

int main()
{
    int a[10] ;
    int i;
    int x,y;
    for (i=0;i<10;i++) a[i]+=1;
    cout<<a;
    cout<<"cin x y"<<endl;
    cin>>x>>y;
    cout<<max (x,y)<<endl;
    return 0;
}

int max(int c,int b)
{
    return (c>b)?c:b;
}
