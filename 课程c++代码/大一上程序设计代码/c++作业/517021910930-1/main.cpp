#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int money;
    double a,b,c,d,e;
    double Quotient,NetValue,IncreaseRate,CurrentValue,Average,CurrentPayoff;
    cout<<"请输入购买金额（>=1000且是1000的整数倍）：";
    for (int i=0;i<10000;i++)
    {cin>>money;
    if((money%1000)==0) break;
    else cout<<money<<"不是1000的整数倍"<<endl<<"请输入购买金额（>=1000且是1000的整数倍）：";}
    cout<<"请输入本周基金运作的每日份额净值"<<endl;
    cin>>a>>b>>c>>d>>e;
    cout<<"Quotient"<<'\t'<<"NetValue"<<'\t'<<"IncreaseRate"<<'\t'<<"CurrentValue"<<'\t'<<"CurrentPayoff"<<endl;
    Quotient=0.985*money;
    CurrentValue=Quotient*a;CurrentPayoff=CurrentValue*0.995-money;IncreaseRate=(a-1)*100;
    cout<<Quotient<<'\t'<<'\t'<<setprecision(4)<<fixed<<a<<'\t'<<'\t'<<setprecision(2)<<fixed<<IncreaseRate<<"%"<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentValue<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentPayoff<<endl;
    CurrentValue=Quotient*b;CurrentPayoff=CurrentValue*0.995-money;IncreaseRate=(b-a)*100/a;
    cout<<Quotient<<'\t'<<'\t'<<setprecision(4)<<fixed<<b<<'\t'<<'\t'<<setprecision(2)<<fixed<<IncreaseRate<<"%"<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentValue<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentPayoff<<endl;
    CurrentValue=Quotient*c;CurrentPayoff=CurrentValue*0.995-money;IncreaseRate=(c-b)*100/b;
    cout<<Quotient<<'\t'<<'\t'<<setprecision(4)<<fixed<<c<<'\t'<<'\t'<<setprecision(2)<<fixed<<IncreaseRate<<"%"<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentValue<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentPayoff<<endl;
    CurrentValue=Quotient*d;CurrentPayoff=CurrentValue*0.995-money;IncreaseRate=(d-c)*100/c;
    cout<<Quotient<<'\t'<<'\t'<<setprecision(4)<<fixed<<d<<'\t'<<'\t'<<setprecision(2)<<fixed<<IncreaseRate<<"%"<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentValue<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentPayoff<<endl;
    CurrentValue=Quotient*e;CurrentPayoff=CurrentValue*0.995-money;IncreaseRate=(e-d)*100/d;
    cout<<Quotient<<'\t'<<'\t'<<setprecision(4)<<fixed<<e<<'\t'<<'\t'<<setprecision(2)<<fixed<<IncreaseRate<<"%"<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentValue<<'\t'<<'\t'<<setprecision(0)<<fixed<<CurrentPayoff<<endl;
    Average=(a+b+c+d+e)/5;
    cout<<setprecision(5)<<fixed<<"Average Net Value in this week ="<<Average;
    return 0;
}
