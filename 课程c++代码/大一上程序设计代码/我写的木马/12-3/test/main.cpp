#include <iostream>
     using namespace std;
     struct link {int data;link*next;};
     link creatsortlist();
     void output(link *c);
     link merge(link *a,link *b);
int main()
{
    cout<<"�����һ������������0������"<<endl;
    link *a;a=new link;*a=creatsortlist();
    cout<<"����ڶ�������������0������"<<endl;
    link *b;b=new link;*b=creatsortlist();
    //cout<<"�Ų����Ұ����������������"<<endl;
    //cout<<"�����ң�"<<endl;
    //cout<<"��֤�漣��ʱ�̣�"<<endl;
    link *c;c=new link;*c=merge(a,b);
    //cout<<"�����������Ѿ���������*_*"<<endl;
    //cout<<"��Ŷ���㿴�������ðɣ��Ұ���������������㿴"<<endl;
    output(c);
    //cout<<"�����ɣ����������*_*"<<endl;
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
