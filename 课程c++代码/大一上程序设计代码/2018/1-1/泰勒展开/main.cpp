#include <iostream>

using namespace std;
 double f(double a);
int main()
{
    double x=0;
    cin>>x;
    cout<<f(x);
    return 0;
}

 double f(double a)
{
    double tmp=1.0,mvp,m=0.5;
    mvp=(a-1)/2;
    double n=1;double i=2;

    while (mvp>=1E-6||mvp<=-1*1E-6)
        {

             tmp+=mvp;

             m=m*(3-2*i)/2;
             i++;
             mvp=mvp*m*(a-1)/i;
             cout<<m<<endl<<mvp<<endl;
         }
    return tmp;
}
