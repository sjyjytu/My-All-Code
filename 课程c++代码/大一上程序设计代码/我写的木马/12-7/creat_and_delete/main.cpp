#include <iostream>

using namespace std;

int main()
{
    int *p;
    p = new int;
    if(!p) {
    cout<<"fuck !"<<endl;
    return 1;}
    *p=20;
    cout<<*p<<endl;
    delete p;
    cout<<*p;
    return 0;
}
