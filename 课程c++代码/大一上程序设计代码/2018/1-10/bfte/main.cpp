#include <iostream>

using namespace std;
class B
{
    friend B fun(B &r1);
    private: int a;
    public: B(int i=0) :a(i) {cout<<"¹¹Ôì£¨"<<i<<endl;}
};
B fun (B &r1) {return r1;}
int main()
{
    B s1(3),s2;
    s2=fun(s1);
    return 0;
}
