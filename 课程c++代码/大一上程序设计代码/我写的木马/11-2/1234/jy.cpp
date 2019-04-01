#include <iostream>

using namespace std;
void c();
int main()
{
    c();c();return 0;
}
void c()
{
    extern int x;
    x*=10;cout<<"x in c is"<<x<<endl;
}
int x=2;

