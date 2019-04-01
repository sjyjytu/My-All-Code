#include <iostream>
     using namespace std;
     struct link {int data;link*next;};
     link creatsortlist();
     void output(link *c);
     link merge(link *a,link *b);
int main()
{
    cout<<"输入第一个升序链表，以0结束："<<endl;
    link *a;a=new link;*a=creatsortlist();
    cout<<"输入第二个升序链表，以0结束："<<endl;
    link *b;b=new link;*b=creatsortlist();
    //cout<<"信不信我把两个链表合起来？"<<endl;
    //cout<<"不信我？"<<endl;
    //cout<<"见证奇迹的时刻："<<endl;
    link *c;c=new link;*c=merge(a,b);
    //cout<<"啦啦啦，我已经合起来啦*_*"<<endl;
    //cout<<"对哦，你看不见，好吧，我把它反向输出来给你看"<<endl;
    output(c);
    //cout<<"厉害吧，给我满分喔*_*"<<endl;
    return 0;
}


link merge(link *a,link *b)
{
   link *p,*q,*m;p=q=m=new link;
   if (a->data<=b->data) {p=a;q=b;}
   else {p=b;q=a;}
   link k=*p;

   while (p->next!=NULL)
   {
       while (p->next!=NULL&&p->next->data<=q->data) p=p->next;
       if (p->next!=NULL) {m=p->next;p->next=q;p=q;q=m;}
       else {p->next=q;break;}
   }
   p->next=q;
   return k;
}

link creatsortlist()
{
    int x;
    link *head,*p,*rear;
    head=rear=new link;
    while (true)
    {
        cin>>x;
        if (x==0) break;
        p=new link;
        p->data=x;
        rear->next=p;
        rear=p;
    }
    rear->next=NULL;
    return *head;
}

void output(link *c)
{
    if (c->next==NULL) cout<<c->data;
    else {output(c->next);cout<<c->data;}
}
