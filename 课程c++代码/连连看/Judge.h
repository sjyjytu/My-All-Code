#ifndef JUDGE_H
#define JUDGE_H

#include <stdlib.h>
#include <cmath>
#include "Map.h"
#include "Press_pos.h"
class Judge
{
private:
	bool isok = 0;//�ж�����Ƿ���Ч

	/*����JY�����㷨��Ԫ��Ϊ��i*100+j������*/
	int *A_zero_tentrix;//A��ʮ��������
	int *B_zero_tentrix;//B��ʮ��������
	int size_A = 0;//one_turn����Ĵ�С��ʵ��������T�ε�
	int size_B = 0;//one_turn����Ĵ�С��ʵ��������T�ε�

	/*����A B���Ե�����Ҫ����һ���������±�������¼ˮƽ�±�*/
	/*��Ϊ��ֱ�������������ģ���ˮƽ�������Ƿֶ������ģ����ֻҪ��¼ˮƽ�ϵĶϵ㼴��*/
	/*����one_turnʱ��A����T��B����T������two_turn���ж�ֻ����������ֱ����ˮƽ���֣�����
	��ȫ����ʱ����A���󲿷ַŵ�����β������¼�Ҳ��ֿ�ʼ���꣬��B���Ҳ��ַŵ�����β������
	��¼�󲿷ֽ����±���Ҳ�����ʼ����,��ǡ���Ҳ�����ʼ�������size_B,���һ�������͹���*/
	int horizontal_A = 0;
	int horizontal_B = 0;

	/*Ϊ�˷��㣬�һ��ǰ�������ʮ����Ĵ�СҲ��¼����*/
	int size_fullA = 0;
	int size_fullB = 0;
	/*A��B��Ҫ���б��������*/
	/*�б�ʱ����A����JY�������ģ�B����JY������+�£������ı�GameWidget�е�A��B*/
	void aleft_bright(press_pos &A,press_pos &B);

	void no_turn(press_pos a, press_pos b, int **map);

	void one_turn();

	void two_turn(press_pos a, press_pos b, int **map);

	void find_a_tentrix(press_pos a, int **map);//find the tentrix of press_pos a

	void find_b_tentrix(press_pos a, int **map);//find the tentrix of press_pos b

	void secret_weapon(press_pos a, press_pos b, int **map);//ok , this is a sb packing

	/*���ᰡ��min max��Ҫ�Լ�д*/
	int judge_min(int x, int y);

	int judge_max(int x, int y);

public:
	/*��¼��ǰ�۵㣬��һ��Ԫ��Ϊ�۵������ڶ���Ԫ��Ϊ����A�۵㣬������Ԫ��Ϊ����B�۵�*/
	/*ע�����AB���п��ܱ��������ģ��ص�GameWidgetʱҪ�ж��Ƿ񱻽�����*/
	int *current_salient;//0-ת������1��2-�۵㣻3��4-����ĵ㣻
	Judge();
	~Judge();
	/*����һ���ܶ�*/
	void have_a_judge(press_pos a, press_pos b, int **map);
	bool get_isok();
};

#endif