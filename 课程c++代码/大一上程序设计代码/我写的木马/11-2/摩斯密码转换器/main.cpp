//Ä¦Ë¹ÃÜÂë×ª»»Æ÷
#include <iostream>
#include<iomanip>
#include<stdlib.h>
using namespace std;

int main()
{
    const int changdu = 100;
    char juzi[changdu+1];
    cin.getline(juzi,changdu+1);
    for (int i=0;juzi[i]!='\0';i++)
    {
        switch (juzi[i]){
        case 'a': cout<<"*-"<<"  ";break;
        case 'b': cout<<"-***"<<"  ";break;
        case 'c': cout<<"-*-*"<<"  ";break;
        case 'd': cout<<"-**"<<"  ";break;
        case 'e': cout<<"*"<<"  ";break;
        case 'f': cout<<"**-*"<<"  ";break;
        case 'g': cout<<"--*"<<"  ";break;
        case 'h': cout<<"****"<<"  ";break;
        case 'i': cout<<"**"<<"  ";break;
        case 'j': cout<<"*---"<<"  ";break;
        case 'k': cout<<"-*-"<<"  ";break;
        case 'l': cout<<"*-**"<<"  ";break;
        case 'm': cout<<"--"<<"  ";break;
        case 'n': cout<<"-*"<<"  ";break;
        case 'o': cout<<"--"<<"  ";break;
        case 'p': cout<<"*--*"<<"  ";break;
        case 'q': cout<<"--*-"<<"  ";break;
        case 'r': cout<<"*-*"<<"  ";break;
        case 's': cout<<"***"<<"  ";break;
        case 't': cout<<"-"<<"  ";break;
        case 'u': cout<<"**-"<<"  ";break;
        case 'v': cout<<"***-"<<"  ";break;
        case 'w': cout<<"*--"<<"  ";break;
        case 'x': cout<<"-**-"<<"  ";break;
        case 'y': cout<<"-*--"<<"  ";break;
        case 'z': cout<<"--**"<<"  ";break;
        case ' ': cout<<endl;break;}

    }
    system("pause");
    return 0;
}
