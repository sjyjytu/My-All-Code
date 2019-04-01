#include <iostream>

using namespace std;

int main()
{
    int quantity,yuan,jiao;
    double charge;
    cout<<"请输入本月用电量：";
    cin>>quantity;
    charge=0.6*quantity;
    cout<<"本月电费为："<<charge<<"元"<<endl;
    //cout<<"charge="<<setprecision(17)<<charge<<endl;
    yuan=charge;
    //cout<<endl;
    //cout<<"(charge-yuan)*10="<<(charge-yuan)*10<<endl;
    jiao=(charge-yuan)*10;
    cout<<yuan<<jiao<<endl;
    return 0;
}
