#include <iostream>
#include<stdlib.h>
using namespace std;
void Hnaoi(int n,char start,char finish,char temp);
int main()
{
  Hnaoi(64,'A','B','C');
  system("pause");
  return 0;
}
void Hnaoi(int n,char start,char finish,char temp)
{
    if (n==1) cout<<start<<"->"<<finish<<" ";
    else {Hnaoi(n-1,start,temp,finish);
          cout<<start<<"->"<<finish<<" ";
          Hnaoi(n-1,temp,finish,start);}
}
