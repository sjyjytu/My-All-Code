#include "head.h"

int main()
{
    cout<<"�����һ������������0������"<<endl;
    link *a=creatsortlist();
    cout<<"����ڶ�������������0������"<<endl;
    link *b;b=new link;b=creatsortlist();

    link *c=merge(a,b);

    output(c);

    return 0;
}
