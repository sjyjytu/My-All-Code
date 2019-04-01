#include <iostream>
const int arsize = 20;

int main()
{
    long long factorials[arsize];
    factorials[1]=factorials[0]=1LL;
    for (int i=2;i<arsize;i++)
        factorials[i]=i*factorials[i-1];
    for(int i=0;i<arsize;i++)
        std::cout<<i<<"!="<<factorials[i]<<std::endl;
        return 0;
}
