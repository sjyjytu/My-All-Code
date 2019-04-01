#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int main()
{
    int a,b,c,x,y,z,i,m=0,n=0;
    srand(time(NULL));
    do
    {a=rand()%10;b=rand()%10;c=rand()%10;}
    while(b==a||a==c||b==c);
    for (n=0,i=0;i<7;i++)
    {
    cout<<"请输入你的数字："<<endl;
    cin>>x>>y>>z;
    if(a==x&&b==y&&c==z) {cout<<"恭喜，你猜对了。";goto L;}
    else {m=((a==x)+(b==y)+(c==z));
          if (x==b||x==c) n++;
          if (y==a||y==c) n++;
          if (z==b||z==a) n++;}
          cout<<m<<"A"<<n<<"B"<<endl;
    }
    cout<<"很遗憾，你没有在规定次数内猜对！答案是："<<a<<b<<c;
    L:return 0;
}
