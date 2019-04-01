#include <iostream>

using namespace std;

int main()
{
    int **a,i,j,k=0;
    a=new int *[3];
    for (i=0;i<3;++i) a[i]=new int[4];
    for (i=0;i<3;i++) for(j=0;j<4;j++) a[i][j]=k++;
    for (i=0;i<3;i++) {cout<<endl; for(j=0;j<4;j++) cout<<a[i][j]<<" ";}
    for (i=0;i<3;i++) delete [] a[i];
    delete []a;
    return 0;
}
