#include <iostream>

using namespace std;
int boss=0;
int a[1000];
int n;
int jy(int );
int min(int x,int y);
int main()
{

    cout << "输入横坐标总个数：" ;
    cin>>n;
    cout<<endl<<"输入每单位宽度横坐标的高度：";
    for (int i=0;i<n;i++) cin>>a[i];
    for (int j=0;j<n;j++) if (a[j] !=0) break;
    jy(j);
    cout<<boss;
    return 0;
}
int jy(int j)
{

    for (int k=j+1;k<n;k++) if (a[k] >=a[j]) break;//要加一段如果全部找完了，找不到比它大的，就要从
    if (k=n&&a[k-1]<a[j]) return jy(j+1);
    else{
    int b=min(a[j],a[k]);
    int sum=0;
    for (int c=0;j<c<k;c++) sum+=(b-a[c]);boss+=sum;
    jy(k-1);
    return boss;}
}

int min(int x,int y)
{
    if (x<=y) return x;
    else return y;
}
