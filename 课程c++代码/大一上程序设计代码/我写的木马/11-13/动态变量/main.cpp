// Assignment 4
// Deng Ruiting  UID: 3035335014
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;int main()
{
   string filenames[20][1];
   string writings[20][200];
   string keyword;
   int n, m;
   n = 0;
   // to read the table_of_content.txt and count the number of documents it contain
   ifstream students;
   students.open("table_of_content.txt");
   if (students.fail())
   {
       cout << "Error in file opening" << endl; exit(1);
   }
   while (students >> filenames[n][0])
   {
       n = n + 1;
   }
   cout << n << " students' text files are read" << endl;
   // to store the writings of students
   for (int i = 0; i < n; i++)
   {
       ifstream content;
       content.open(filenames[i][0]);
       if (content.fail())
       {
           cout << "Error in file opening" << endl; exit(1);
       }
       content >> writings[i][200];
       content.close();
   }
   students.close();
   while (1 == 1)
   {
       cout << "-----" << endl;
       cout << "Options:" << endl;
       cout << "1.Keyword search" << endl;
       cout << "2.Exit" << endl;
       cout << "Your choice:" << endl;
       cin >> m;
       if (m == 1)
       {
           cout << "The key word is " << endl;
           cin >> keyword;
           for (int i = 0; i < n; i++)
           {
               int number = 0;
               int pos = writings[i][200].find(keyword);
               while (pos != string::npos)
               {
                   number = number + 1;
                   pos = writings[i][200].find(keyword, pos + 1);
               }
               cout << filenames[i][0] << " " << number << endl;
           }
       }
       else break;
   }
   return 0;
}
