#include <iostream>

using namespace std;
long f(int n);
int main()
{
    int n;
    cout<<"ÊäÈënµÄÖµ";
    cin>>n;
    cout << f(n);
    return 0;
}
long f(int n)
{
    if (n==0) return 0;
    else if (n==1) return 1;
    else return (f(n-1)+f(n-2));
}
