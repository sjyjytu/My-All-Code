#include "head.h"

int main()
{
    cout<<"输入第一个升序链表，以0结束："<<endl;
    link *a=creatsortlist();
    cout<<"输入第二个升序链表，以0结束："<<endl;
    link *b;b=new link;b=creatsortlist();

    link *c=merge(a,b);

    output(c);

    return 0;
}
