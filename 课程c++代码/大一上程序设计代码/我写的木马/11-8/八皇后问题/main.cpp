#include <iostream>
#include<stdlib.h>
using namespace std;
void queen_all(int k);
int col[9];
bool row[9],digleft[17],digright[17];
int main()
{
    int j;
    for (j=0;j<=8;j++) row[j]=true;
    for(j=0;j<=16;j++) digleft[j]=digright[j]=true;
    queen_all(1);
    return 0;
}
void queen_all(int k)
{
    int i ,j;
    char awn;
    for (i=1;i<9;i++) if (row[i]&&digleft[k+i-1]&&digright[8+k-i])
    {col[k]=i;
    row[i]=digleft[k+i-1]=digright[8+k-i]=false;
    if (k==8){
    for(j=1;j<=8;j++) cout<<j<<" "<<col[j]<<'\t';
    cout<<endl<<"是否需要继续寻找（Q--退出，其他键继续：）";
    cin>>awn;
    if (awn=='Q'||awn=='q') exit(0);
    }
    else queen_all(k+1);
    row[i]=digleft[i+k-1]=digright[8+k-i]=true;
 }
}
