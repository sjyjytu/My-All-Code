#include <iostream>

using namespace std;
void f(int i);
int n;int a[100];
int main()
{
    cout<<"���������鳤�ȣ�";
    cin>>n;
    cout<<"�������飺";
    for (int k=0;k<n;k++) cin>>a[k];
    f(0);
    for (int j=0;j<n;j++) cout<<a[j]<<"  ";
    return 0;
}
void f(int i)
{
    int k;
    if (i<n/2) {k=a[i];a[i]=a[n-i-1];a[n-i-1]=k;f(i+1);}
}

