#include <iostream>

using namespace std;

int main()
{
    int quantity,yuan,jiao;
    double charge;
    cout<<"�����뱾���õ�����";
    cin>>quantity;
    charge=0.6*quantity;
    cout<<"���µ��Ϊ��"<<charge<<"Ԫ"<<endl;
    //cout<<"charge="<<setprecision(17)<<charge<<endl;
    yuan=charge;
    //cout<<endl;
    //cout<<"(charge-yuan)*10="<<(charge-yuan)*10<<endl;
    jiao=(charge-yuan)*10;
    cout<<yuan<<jiao<<endl;
    return 0;
}
