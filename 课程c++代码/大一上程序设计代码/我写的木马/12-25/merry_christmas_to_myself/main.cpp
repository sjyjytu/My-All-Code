#include <iostream>

using namespace std;
template <class elem> class link;
template <class T> ostream &operator<<(ostream &,const link<T>&);//T can be elem?
template <class elem> class node;

template <class elem>
class node
{
friend class link<elem>;
friend ostream &operator<<(ostream &,const link<elem>&);

private:
      elem data;
      node<elem> *next;
public:
      node(const elem &x,node <elem> *N=NULL) {data=x;next=N;}
      node():next(NULL){}//;?
      ~node(){}

};
template <class elem>
class link{
         friend ostream&operator<<(ostream &os,const link<elem>&obj){
         node<elem> *q=obj.head->next;
    os<<endl;
    while (q!=NULL) {os<<q->data;q=q->next;}
    return os;
         }
    protected:
              node<elem> *head;
              void make_empty();
    public:
           link() {head=new node<elem>;}
           ~link(){make_empty();delete head;}

           void create(const elem &flag);
};

template<class elem>
void link<elem>::create(const elem &flag)//what do they mean
{
    elem tmp;
    node<elem>*p,*q=head;
    cout<<"请输入链表数据，"<<flag<<"表示结束"<<endl;
    while (true)
    {
        cin>>tmp;
        if(tmp==flag) break;
        p=new node<elem>(tmp);
        q->next=p;
        q=p;
    }
}

template<class elem>
void link<elem>::make_empty()
{
    node<elem> *p=head->next,*q;
    head->next=NULL;
    while (p!=NULL) {q=p->next;delete p;p=q;}
}

template<class T>
ostream &operator<<(ostream &os,const link<T> &obj)
{
    node<T> *q=obj.head->next;
    os<<endl;
    while (q!=NULL) {os<<q->data;q=q->next;}
    return os;
}


int main()
{
    link<int> abc;
    abc.create(0);
    cout<<abc;
    return 0;
}
