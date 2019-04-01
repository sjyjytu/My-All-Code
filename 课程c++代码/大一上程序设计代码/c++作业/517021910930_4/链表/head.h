#ifndef dec2
     #define dec2
     #include <iostream>
     using namespace std;
     struct link {int data;link*next;};
     link* creatsortlist();
     void output(link *c);
     link* merge(link *a,link *b);
#endif
