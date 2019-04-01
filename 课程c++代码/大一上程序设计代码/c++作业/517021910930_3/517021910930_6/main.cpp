#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("input.txt");
    if (!in) {cerr<<"create file error\n";return 1;}//*****************************************************
    int n,m1=0,f1=0,m2=0,f2=0;
    //cout << "������������";
    in>>n;
    //cout<<"�������ı���(ע�⣺�������һ�����ڵ�ÿһ�е���󶼱����пո�"<<endl;

    char a[50]={'\0'};
    char b[100]={'\0'};
    char c[4]={'\0'};
    string A;
    string B;
    in.get();
    for (int i=1;i<=n;i++)
    {
      in.getline(a,50,'-');
      in.getline(c,4,' ');
      in.getline(b,100);
      string x(&a[0],&a[strlen(a)]);
      string y(&b[0],&b[strlen(b)]);//�������a��bת��Ϊstring����
//��ȥ��ͬ��֮���x�Լ��ظ��ĵ��ʲ��������ظ���x���ӵ�A���棺
    string::size_type idx=A.find(x);
    if (idx==string::npos) A+=x;
//��ȥy��ͬ�е�x�ظ��ĵ��ʲ���������x�ظ���y���ӵ�B���棺
    string::size_type idy=y.find(x);
    if (idy==string::npos) B+=y;
    else
        {
            int p=y.find(x,0);
            y.erase(p,x.length());
            B+=y;
        }
    }
//A�ѽ����
//��A��B�ֱ�ת�����ַ�����jy1��jy2���Ա��ȥB�ڵ��ظ�  �ͳ�ȥ����û��������⣺��ͬ�е�y��x�ظ���
    char jy1[500],jy2[500];
    char yx1[500][50],yx2[500][50];
    strncpy(jy1,A.c_str(),A.length());
    strncpy(jy2,B.c_str(),B.length());
//�ָ�A���ʣ�
    for (int j=0;j<strlen(jy1);j++)
    {
        if (jy1[j] !=' ') {yx1[m1][f1]=jy1[j];f1+=1;}
        else {m1+=1;f1=0;}
    }
//�ָ�B�ĵ��ʣ�
    for (int j2=0;j2<strlen(jy2);j2++)
    {
        if (jy2[j2] !=' ') {yx2[m2][f2]=jy2[j2];f2+=1;}
        else {m2+=1;f2=0;}
    }
//��ȥB�Լ��ظ���
    int sign[500]={0};
    for (int t=0;t<m2;t++)
       for (int t2=t+1;t2<m2;t2++)
          if (strcmp(yx2[t],yx2[t2])==0)
              sign[t2]=1;
//*��ȥ������A�ظ���B��
    for (int ic=0;ic<m1;ic++)
         for (int ic2=0;ic2<m2;ic2++)
             if (strcmp(yx1[ic],yx2[ic2])==0) sign[ic2]=1;

    in.close();
//�����
    ofstream out("output.txt");
    if (!out) {cerr<<"open file error\n"<<endl;return 1;}//*********************************************

    out<<"A�Ĳ���Ϊ��";
    for (int th=0;th<m1;th++)
      {
        out<<yx1[th]<<",";
      }
    out<<endl;
    out<<"B�Ĳ���Ϊ��";
    for (int ff=0;ff<m2;ff++)
        {if (sign[ff]==0)
           {
               out<<yx2[ff];
               if (ff<m2-1)
                  out<<",";
            }
        }
    out.close();
    return 0;
}
