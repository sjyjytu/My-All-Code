#include "book.h"

Book::Book(const char *s,int totalNo)
{
    no=totalNo;borrowed=0;strcpy(name,s);
}

void Book::borrow(int readerNo)
{
    if (borrowed!=0) cerr<<"�����ѱ��裬�����ظ���\n";else borrowed=readerNo;
}

void Book:: Return()
{
    if (borrowed==0) cerr<<"����û�б��裬�����Թ黹\n";else borrowed=0;
}

void Book::display()
{
    cout<<setw(10)<<no<<setw(20)<<name<<setw(10)<<borrowed<<endl;
}
