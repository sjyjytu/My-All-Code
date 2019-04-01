#ifndef _book_h
#define _book_h

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

class Book
{
    int no;
    char name[20];
    int borrowed;
public:
    Book(const char *s="",int total_no=0) ;
    void borrow (int readerNo);
    void Return();
    void display();
};
#endif
