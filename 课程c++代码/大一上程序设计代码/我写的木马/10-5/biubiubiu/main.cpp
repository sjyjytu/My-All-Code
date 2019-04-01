#include <iostream>

using namespace std;
int stonel(int);
int main()
{
   int stone ;
   cout<<"enter the weight in stone:";
   cin>>stone;
   int pounds=stonel(stone);
   cout <<stone<<"stones=";
   cout <<pounds<<"pounds."<<endl;
   return 0;
}
int stonel(int sts)
{
    return 14*sts;
}
