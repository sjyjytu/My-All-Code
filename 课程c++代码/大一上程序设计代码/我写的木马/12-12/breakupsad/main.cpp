#include <iostream>

using namespace std;

int main()
{
    int a,b;
    int i=10,j=10;
    a=(i++)+(i++)+(i++);
    b=(++j)+(++j)+(++j);
    cout<<a<<endl<<b<<endl;
    return 0;
}
