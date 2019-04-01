#include <iostream>

using namespace std;
class T
{
    public:
           T(){a=0;b=0;c=0;}
           T(int i,int j,int k){a=i;b=j;c=k;}
           void get(int &i,int &j,int&k) {i=a;j=b;k=c;}
           T operator* (T obj);
    private:
           int a,b,c;
};
T T::operator*(T obj)
{
    T temp;
    temp.a=a*obj.a;
    temp.b=b*obj.b;
    temp.c=c*obj.c;
    return temp;
}
int main()
{
    T obj1(1,2,3),obj2(5,5,5),obj3;
    int a=1,b=2,c=3;
    obj3=obj1*obj2;
    //obj3.get(a,b,c);
    cout<<"(obj1*obj2):\t"<<a<<' '<<b<<' '<<c<<endl;
    (obj2*obj3).get(a,b,c);
    cout<<a<<' '<<b<<' '<<c;
    return 0;
}
