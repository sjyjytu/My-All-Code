#ifndef RECORDER_H
#define RECORDER_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Judge.h"
using namespace std;
class Recorder
{
private:
	fstream file;
	int last_pos;
	
public:
	Recorder();
	~Recorder();
	int operations[5];
	void save_operation(Judge &,int n = 0);
	void save_now(Map &,int , int , int , int , int , int pt=0,int svn=0);
	void read_map(Map &, int&, int&, int&, int&,int &,int pt,int rdn);//����ͼ
	void read_oper(int n=0);//�ط�ģʽ�¶�ȡ����
	void clear_operation(int n);//ר����������һ��operation.txt
};
#endif // !RECORDER_H