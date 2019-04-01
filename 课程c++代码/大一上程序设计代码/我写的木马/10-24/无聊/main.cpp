#include <iostream>

using namespace std;

int main()
{
   char str[81];
   int sum=0,data,i=0,flag;
   cin.getline(str,81);
   while (str[i]==' ') ++i;
   while (str[i]!='\0')
     {if (str[i] !='0') flag=10;
     else {if (str[i+1]=='x'||str[i+1]=='X') {flag=16;i+=2;}
     else {flag=8;i++;}
                   }
    data=0;
    switch (flag) {
    case 10: while(str[i]!=' '&&str[i]!='\0')
    data=data*10+str[i++]-'0';break;
    case 8: while (str[i]!=' '&&str[i]!='\0')
    data=data*8+str[i++]-'0';break;
    case 16: while (str[i]!=' '&&str[i]!='\0')
    {data=data*16;if(str[i]>='A'&&str[i]<='F') data=data+str[i++]-'A'+10;
    else if(str[i]>='a'&&str[i]<='f') data=data+str[i++]-'a'+10;
    else data=str[i++]-'0';}
                   }
    sum+=data;
    while (str[i]==' ') ++i;}
 cout<<sum<<endl;
 return 0;}
