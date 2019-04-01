#include <iostream>
#include <cstring>
using namespace std;
char *sub(char *s,int start,int end);
int main()
{
    char *a;char ch[]="aobfabfioafiaowdiowfioaw";a=ch;
    cout<<sub(a,0,13);
    return 0;
}

char *sub(char *s,int start,int end)
{
    int len = strlen(s);
    if (start<0||start >=len||end<0||end>=len||start>end) {cout<<"起始或终止位置错误"<<endl;return NULL;}
    char *su=new char[end-start+2];
    strncpy(su,s+start,end-start+1);
    su[end-start+1]='\0';
    return su;
}
