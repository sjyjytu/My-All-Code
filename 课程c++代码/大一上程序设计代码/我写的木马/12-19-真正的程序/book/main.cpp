#include "book.h"

void initialize();
void addbook();
void borrowbook();
void returnbook();
void displaybook();

int main()
{
    int selector;
    while (true)
      {
          cout<<"0--�˳�\n";
          cout<<"1--��ʼ���ļ�\n";
          cout<<"2--�����\n";
          cout<<"3--����\n";
          cout<<"4--����\n";
          cout<<"5--��ʾ������Ŀ��Ϣ\n";
          cout<<"��ѡ��0-5����";cin>>selector;
        if (selector==0) break;
        switch(selector)
        {
            case 1:initialize();break;
            case 2:addbook();break;
            case 3:borrowbook();break;
            case 4:returnbook();break;
            case 5:displaybook();break;
        }
      }
    return 0;
}

void initialize()
{
    ofstream out("book.txt");
    int no=0;
    out.write(reinterpret_cast<const char*> (&no),sizeof(int));
    out.close();
}

void addbook()
{
    char ch[20];
    Book *bp;
    int no;
    fstream out("book.txt");
    //�����������
    out.seekg(0);
    out.read(reinterpret_cast<char*>(&no),sizeof(int));
    //������Ҫ��ӵ����飺
    ++no;
    cout<<"������������";cin>>ch;
    bp=new Book(ch,no);

    //��������Ϣ��ӵ��ļ���
    out.seekp(0,ios::end);
    out.write(reinterpret_cast<const char*>(bp),sizeof(*bp));//out.write(reinterpret_cast<char*>(&bp),sizeof(Book));
    delete bp;

    //���²�������
    out.seekp(0);
    out.write(reinterpret_cast<const char*>(&no),sizeof(int));
    out.close();
}

void borrowbook()
{
    int bookno,readerno;
    fstream io("book.txt");
    Book bk;
    cout<<"��������źͶ��ߺţ�";
    cin>>bookno>>readerno;
    io.seekg((bookno-1)*sizeof(Book)+sizeof(int));
    io.read(reinterpret_cast<char*>(&bk),sizeof(Book));
    bk.borrow(readerno);
    io.seekp((bookno-1)*sizeof(Book)+sizeof(int));
    io.write(reinterpret_cast<const char*>(&bk),sizeof(Book));
    io.close();
}

void returnbook()
{
    int bookno;
    fstream io("book.txt");
    Book bk;
    cout<<"��������ţ�";
    cin>>bookno;
    io.seekg((bookno-1)*sizeof(Book)+sizeof(int));
    io.read(reinterpret_cast<char*>(&bk),sizeof(Book));
    bk.Return();
    io.seekp((bookno-1)*sizeof(Book)+sizeof(int));
    io.write(reinterpret_cast<const char*>(&bk),sizeof(Book));
    io.close();
}

void displaybook()
{
    ifstream in("book.txt");
    Book bk;
    in.seekg(sizeof(int));
    in.read(reinterpret_cast<char*>(&bk),sizeof(Book));
    while(!in.eof())
    {
        bk.display();
        in.read(reinterpret_cast<char*>(&bk),sizeof(Book));
    }
    in.close();
}







