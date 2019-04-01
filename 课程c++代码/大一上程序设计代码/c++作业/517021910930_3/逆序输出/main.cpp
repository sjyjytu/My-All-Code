#include <iostream>
#include<stdlib.h>
using namespace std;
int str[80];
void zsm(int );
int main()
{
    int n;
    cout<<"输入数组长度：";
    cin>>n;
    cout<<"输入数组："<<endl;
    for (int i=0;i<n;i++) cin>>str[i];
    zsm(n-1);
    return 0;
}
void zsm(int k)
{
    cout<<str[k]<<" ";
    if (k==0) return ;
    else zsm(k-1);
}
