#include<iostream>
#include<stdlib.h>
using namespace std;

int main()
{
    double a[]={53.2,48,9};double i1=0.5,i2=0.7,i3=0.9;
    double b[]={74.5,68,13};
    double c[]={95.8,88,17};
    double a1=(a[0]*a[0]-a[1]*a[1]-a[2]*a[2])/(2*a[1]*a[2]);
        double b1=(b[0]*b[0]-b[1]*b[1]-b[2]*b[2])/(2*b[1]*b[2]);
         double c1=(c[0]*c[0]-c[1]*c[1]-c[2]*c[2])/(2*c[1]*c[2]);
         double a2=a[2]*a1/i1;
         double b2=b[2]*b1/i2;
         double c2=c[2]*c1/i3;
         cout<<a2<<' '<<b2<<' '<<c2<<' '<<endl;
  system("pause");
    return 0;
}

