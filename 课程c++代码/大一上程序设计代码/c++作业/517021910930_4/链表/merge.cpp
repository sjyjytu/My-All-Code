#include "head.h"

link* merge(link *a,link *b)
{
   link *p,*q,*m;p=q=m=new link;
   if (a->data<=b->data) {p=a;q=b;}
   else {p=b;q=a;}
   link* k=p;
   while (p->next!=NULL)
   {
       while (p->next!=NULL&&p->next->data<=q->data) p=p->next;
       if (p->next!=NULL) {m=p->next;p->next=q;p=q;q=m;}
       else {p->next=q;break;}
   }
   p->next=q;
   return k;
}
