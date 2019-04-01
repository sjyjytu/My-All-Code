#include "head.h"

link* creatsortlist()
{
    int x;
    link *head,*g,*rear;
    head=rear=new link;
    while (true)
    {
        cin>>x;
        head->data=x;
        break;
    }
    while (true)
    {
        cin>>x;
        if (x==0) break;
        g=new link;
        g->data=x;
        rear->next=g;
        rear=g;
    }
    rear->next=NULL;
    return head;
}
