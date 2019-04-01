 #include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
  int i;
  cout<<"argc="<<argc<<endl;
  for (i=0;i<argc;++i)
  {
      cout<<"argc["<<i<<"]="<<argv[i]<<endl;
  }
  return 0;}
