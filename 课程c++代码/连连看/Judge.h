#ifndef JUDGE_H
#define JUDGE_H

#include <stdlib.h>
#include <cmath>
#include "Map.h"
#include "Press_pos.h"
class Judge
{
private:
	bool isok = 0;//判断这次是否有效

	/*引入JY零阵算法，元素为（i*100+j）坐标*/
	int *A_zero_tentrix;//A的十字形零阵
	int *B_zero_tentrix;//B的十字形零阵
	int size_A = 0;//one_turn零阵的大小，实际上他是T形的
	int size_B = 0;//one_turn零阵的大小，实际上他是T形的

	/*根据A B各自的需求，要定义一个辅助的下标数来记录水平下标*/
	/*因为竖直方向总是连续的，而水平方向总是分段连续的，因此只要记录水平上的断点即可*/
	/*由于one_turn时，A是右T，B是左T，并且two_turn的判定只单独关心竖直或者水平部分，所以
	补全零阵时，将A的左部分放到数组尾部并记录右部分开始坐标，将B的右部分放到数组尾部，并
	记录左部分结束下标和右部分起始坐标,但恰好右部分起始坐标就是size_B,因此一个辅助就够了*/
	int horizontal_A = 0;
	int horizontal_B = 0;

	/*为了方便，我还是把完整的十字阵的大小也记录下来*/
	int size_fullA = 0;
	int size_fullB = 0;
	/*A、B是要被判别的两个点*/
	/*判别时，将A放在JY矩阵中心，B放在JY矩阵右+下，但不改变GameWidget中的A、B*/
	void aleft_bright(press_pos &A,press_pos &B);

	void no_turn(press_pos a, press_pos b, int **map);

	void one_turn();

	void two_turn(press_pos a, press_pos b, int **map);

	void find_a_tentrix(press_pos a, int **map);//find the tentrix of press_pos a

	void find_b_tentrix(press_pos a, int **map);//find the tentrix of press_pos b

	void secret_weapon(press_pos a, press_pos b, int **map);//ok , this is a sb packing

	/*心酸啊，min max都要自己写*/
	int judge_min(int x, int y);

	int judge_max(int x, int y);

public:
	/*记录当前折点，第一个元素为折点数，第二个元素为靠近A折点，第三个元素为靠近B折点*/
	/*注意这个AB是有可能被交换过的，回到GameWidget时要判断是否被交换过*/
	int *current_salient;//0-转弯数；1，2-折点；3，4-点击的点；
	Judge();
	~Judge();
	/*这是一个总督*/
	void have_a_judge(press_pos a, press_pos b, int **map);
	bool get_isok();
};

#endif