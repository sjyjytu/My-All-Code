#include <iostream>

using namespace std;
void make_change(int coins[],int differentcoins, int maxchange,int coinused[]);
int main()
{
    int n,k,*p,*q;
    cout<<"�����벻ͬ��ֵ��Ӳ������"<<endl;
    cin>>n;
    cout<<"�������ֵ��"<<endl;
    p=new int [n];
    for (int i=0;i<n;i++) cin>>p[i];
    cout<<"Ҫ�ҵ�Ǯ��"<<endl;
    cin>>k;
    q=new int [k+1];
    make_change(p,n,k,q);
    cout<<"����Ҫ��"<<q[k];
}

void make_change(int coins[],int differentcoins, int maxchange,int coinused[])
{
    coinused[0]=0;
    for (int cents=1;cents<=maxchange;cents++)
    {
        int mincoins=cents;
        for (int j=0;j<differentcoins;j++)
        {
            if (coins[j]>cents) continue;
            if (coinused[cents-coins[j]]+1<mincoins) mincoins=coinused[cents-coins[j]]+1;
        }
        coinused[cents]=mincoins;
    }

}
