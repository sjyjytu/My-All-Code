 #include <iostream>

using namespace std;
int change(char *);
int main(int argc,char *argv[])
{
  int sum=0;
  for (int i=1;i<argc;++i) sum+=change(argv[i]);
  cout<<sum/(argc-1)<<endl;

  return 0;
}
int change(char *s)
{
    int num=0;
    while(*s) {num=num*10+*s-'0';++s;}
    return num;
}
