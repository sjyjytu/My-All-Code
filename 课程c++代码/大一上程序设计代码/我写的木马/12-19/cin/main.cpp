#include <iostream>
#include <fstream>
using namespace std;
//ostream&tab(ostream &os) {return os<<'\t';}
int main()
{
    //char ch[5],ch1;cin.get(ch,5,'.');cout<<ch[0]<<endl;cout<<ch[1]<<endl;cin>>ch1;cout<<"ch1="<<ch1;
    //char buff[80];cout<<"enter a sentence:"<<endl;cin.read(buff,20);cout.write(buff,cin.gcount());cout<<endl;cout<<"一共输入了"<<cin.gcount()<<"个字符。";cout<<buff[6];
    //int n;cout<<"enter a octal number:";cin>>oct>>n;cout<<"octal"<<oct<<n<<"in hex is:"<<hex<<n<<'\n';cout<<setbase(16)<<"octal"<<n<<"in dec is:"<<setbase(10)<<n<<endl;
    //double x=123.456789,y=9876.54321;for (int i=9;i>0;i--){cout<<setprecision(i)<<x<<'\t'<<y<<endl;}
    //char ch[5];//int p=100;
    //cin>>setw(5)>>ch; cout<<setfill('*')<<left<<setw(10)<<ch;cout<<setw(10)<<right<<"wwe"<<setw(10)<<1234<<'a'<<endl;
    //int a=5,b=9;cout<<a<<tab<<b;
    ofstream out("nibaba");
    ifstream in;
    int i;
    if (!out) {cerr<<"create file error\n";return 1;}
    for (i=0;i<=10;i++) {out<<i<<' ';}
    out.close();
    in.open("nibaba");
    if (!in) {cerr<<"create file error\n";return 1;}
    while (in>>i) cout<<i<<' ';
    in.close();
    return 0;
}
