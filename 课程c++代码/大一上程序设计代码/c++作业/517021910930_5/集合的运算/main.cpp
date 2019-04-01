#include <iostream>

using namespace std;

class integerset
{
      friend integerset operator+ (const integerset &r1,const integerset &r2);
      friend integerset operator- (const integerset &r1,const integerset &r2);
      friend integerset operator* (const integerset &r1,const integerset &r2);
      friend void operator/ ( integerset &r1, integerset &r2);
      friend bool operator== (const integerset &r1,const integerset &r2);
      friend istream& operator>>(istream &in,  integerset &obj);
      friend ostream& operator<<(ostream &os, const integerset &obj);



    private:
      static const int max =100;
      int inset [max];
      int length;
      int b[max];
    public:
      integerset();  //默认构造
      integerset(int [],int n); //赋值构造
      void insert_(int); //插入一个元素
      void delete_(int); //删除一个元素
      integerset &operator= ( const integerset &r1);


};

ostream& operator<<(ostream &os, const integerset &obj)
{
    bool isempty=true;
    cout<<"{";
    for (int i=0;i<obj.max;i++)
      if (obj.inset[i]==1)
        {os<<i<<" ";isempty=false;}
    if (isempty) cout<<"- - -";
    cout<<"}";
    return os;
}

istream& operator>>(istream &in,  integerset &obj)
{
    in>>obj.length;
    for (int i=0;i<obj.length;i++)
    {in>> obj.b[i];obj.inset[obj.b[i]]=1;}
    return in;
}

integerset::integerset()
{
    for(int i=0;i<max;i++) {inset[i]=0;b[i]=0;}
    length=0;//****
}

integerset::integerset(int a[],int n)
{
    for(int i=0;i<max;i++) {inset[i]=0;b[i]=0;}
    for(int i=0;i<max||i<n;i++) inset[a[i]]=1;
    length=0;//******
}

void integerset::insert_(int element)
{
    if(element<0||element>=max) return ;
    if(inset[element]==1) return ;
    else  inset[element]=1;
}

void integerset::delete_(int element)
{
    if(element<0||element>=max) return;
    if(inset[element]==0) return;
    else inset[element]=0;
}

integerset operator+ (const integerset &r1,const integerset &r2)
{
    integerset tmp;
    int i;
    for (i=0;i<tmp.max;i++)
      {
          if (r1.inset[i]==1||r2.inset[i]==1) tmp.inset[i]=1;
      }
    return tmp;
}

integerset operator- (const integerset &r1,const integerset &r2)
{
    integerset tmp;
    for (int i=0;i<tmp.max;i++)
      {
          if (r1.inset[i]==1&&r2.inset[i]==0) tmp.inset[i]=1;
      }
    return tmp;
}
integerset operator* (const integerset &r1,const integerset &r2)
{
    integerset tmp;
    for (int i=0;i<tmp.max;i++)
      {
          if (r1.inset[i]==1&&r2.inset[i]==1) tmp.inset[i]=1;
      }
    return tmp;
}
void operator/ ( integerset &r1, integerset &r2)
{
    integerset tmp;
    for (int i=0;i<tmp.max;i++)
      {
          tmp.inset[i]=r1.inset[i];
      }
    for (int i=0;i<tmp.max;i++)
      {
          r1.inset[i]=r2.inset[i];
      }
    for (int i=0;i<tmp.max;i++)
      {
         r2.inset[i]=tmp.inset[i];
      }
}
bool operator== (const integerset &r1,const integerset &r2)
{
    for (int i=0;i<r1.max;i++)
     {
         if (r1.inset[i]!=r2.inset[i]) return false;
     }
    return true;
}

integerset &integerset::operator= ( const integerset &r1)
{
    if (this==&r1) return *this;
    for (int i=0;i<r1.max;i++) {inset[i]=r1.inset[i];}
    return *this;
}
int main()
{
    integerset r1, r2,r3;
    cout<<"输入格式为：元素个数 元素1 元素2 ……"<<endl;
    cout<<"如，数组{1，2，3}的输入方法为：3 1 2 3"<<endl;
    cout<<"请输入r1和r2：";
    cin>>r1>>r2;
    if(r1==r2) cout<<"r1==r2"<<endl;
    else cout<<"r1!=r2"<<endl;
    r3=r1+r2;
    cout<<"r1+r2="<<r3<<endl;
    r3=r1-r2;
    cout<<"r1-r2="<<r3<<endl;
    r3=r1*r2;
    cout<<"r1*r2="<<r3<<endl;
    cout<<"r1/r2:";
    r1/r2;
    cout<<"r1="<<r1<<' '<<"r2="<<r2;
    return 0;
}


