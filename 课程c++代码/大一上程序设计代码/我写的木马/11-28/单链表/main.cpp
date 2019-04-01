#include <iostream>

using namespace std;
struct singlelink{int data; singlelink *next;};
int main()
{
    singlelink *p,*head,*rear;
    int x;
    head=rear=new singlelink;
    while (!0)
      {cin>>x;
       if (x==0) break;
       p=new singlelink;
       p->data=x;
       rear->next=p;
       rear=p;}
    rear->next=NULL;
    cout<<"链表的内容为："<<endl;
    p=head->next;
    while (p!=NULL) {cout<<p->data<<" ";p=p->next;}
    return 0;
}
