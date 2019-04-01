#include <iostream>
#include<string.h>
using namespace std;
void qp(char str[],int);
void swap(char str[],int,int);
void biubiu(char str[]);
int main()
{
    char str[]="ABCDE";
    biubiu(str);
    return 0;
}
void qp(char str[],int k)
{   int i;
    if (k==strlen(str)) cout<<str<<endl;
    else for(i=k;i<strlen(str);i++) {swap(str,i,k);qp(str,k+1);swap(str,i,k);}
}
void swap(char str[],int i,int j)
{
    int tmp;
    tmp=str[i];
    str[i]=str[j];
    str[j]=tmp;
}
void biubiu(char str[])
{
    qp(str,0);
}
