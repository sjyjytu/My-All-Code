#include "book.h"

Book::Book(const char *s,int totalNo)
{
    no=totalNo;borrowed=0;strcpy(name,s);
}

void Book::borrow(int readerNo)
{
    if (borrowed!=0) cerr<<"本书已被借，不能重复借\n";else borrowed=readerNo;
}

void Book:: Return()
{
    if (borrowed==0) cerr<<"本书没有被借，不可以归还\n";else borrowed=0;
}

void Book::display()
{
    cout<<setw(10)<<no<<setw(20)<<name<<setw(10)<<borrowed<<endl;
}
