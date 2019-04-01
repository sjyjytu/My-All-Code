#include "Judge.h"

void Judge::aleft_bright(press_pos &posA, press_pos &posB)
{
	if ((posA.getx() > posB.getx()) || (posA.getx() == posB.getx() && posA.gety() > posB.gety()))
	{
		press_pos temp_pos = posB;
		posB = posA;
		posA = temp_pos;
	}
}

void Judge::have_a_judge(press_pos a, press_pos b, int ** map)
{
	/*真正的做事情的函数*/
	/*将is_ok置零*/
	isok = 0;
	/*先把a b放在理想的判断位置，（参考写代码历程*/
	aleft_bright(a, b);
	/*然后把可能交换过的a b存在current_salient中*/
	current_salient[3] = a.getx() * 100 + a.gety();
	current_salient[4] = b.getx() * 100 + b.gety();
	//判断是否同一种图案：
	if (map[a.getx()][a.gety()] == map[b.getx()][b.gety()])
	{
		/*判断有无路径：下列4种情况一次只可能出现一种*/
		//1. B1: 4 roads , one or two turns
		if (a.getx() < b.getx() && a.gety() > b.gety())
		{
			secret_weapon(a, b, map);
			one_turn();
			if (isok != 1) two_turn(a, b, map);
		}

		//2. B2: 3 roads , no or two turns
		else if (a.getx() < b.getx() && a.gety() == b.gety())
		{
			no_turn(a, b, map);
			if (isok != 1) {
				secret_weapon(a, b, map);
				two_turn(a, b, map);
			}
		}

		//3. B3: 4 roads , one or two turns
		else if (a.getx() < b.getx() && a.gety() < b.gety())
		{
			secret_weapon(a, b, map);
			one_turn();
			if (isok != 1) two_turn(a, b, map);
		}

		//4. B4: 3 roads , no or two turns
		else if (a.getx() == b.getx() && a.gety() < b.gety())
		{
			no_turn(a, b, map);
			if (isok != 1)
			{
				secret_weapon(a, b, map);
				two_turn(a, b, map);
			}
		}
	}

	/*not the same icon*/
	else isok = 0;
}

void Judge::no_turn(press_pos a, press_pos b, int ** map)
{
	//不拐弯，包括在横竖直线和直接相邻,满足前提：横坐标或纵坐标相等
	if (a.getx() == b.getx())
	{
		//这是B4的竖直情况
		isok = 1;//用反证法，先假设它有通路
		/*假设成立时的第一个元素为0*/
		current_salient[0] = 0;
		for (int i = 1; i < b.gety() - a.gety(); i++)
		{
			if (map[a.getx()][a.gety() + i] != 0)
			{
				//假设不成立
				isok = 0;
				current_salient[0] = -1;
				break;
			};
		}
	}
	else if (a.gety() == b.gety())
	{
		//这是B2的水平情况
		isok = 1;//用反正法，先假设它有通路
		current_salient[0] = 0;
		//if (b.getx()-a.getx()==1) 
		for (int i = 1; i < b.getx() - a.getx(); i++)
		{
			if (map[a.getx() + i][a.gety()] != 0)
			{
				//假设不成立
				isok = 0;
				current_salient[0] = -1;
				break;
			};
		}

	}
}

void Judge::one_turn()
{
	//一个弯
	//算法是把A的十字形0阵和B的十字形零阵求出来，遍历A的零阵，看与B的零阵有无交点
	//我好像无法知道零阵的大小。。。。咋办！
	//算了 我还是浪费空间好了。。。
	if (A_zero_tentrix[size_A - 1] / 100 < B_zero_tentrix[size_B - 1] / 100 &&
		B_zero_tentrix[0] / 100 > A_zero_tentrix[0] / 100) return;//肯定没有交点
	for (int i = 0; i < size_A; i++)
	{
		for (int j = 0; j < size_B; j++)
		{
			if (A_zero_tentrix[i] == B_zero_tentrix[j])
			{
				isok = 1;
				current_salient[0] = 1;
				current_salient[1] = A_zero_tentrix[i];
				break;
			}
			else if ((A_zero_tentrix[i] / 100) < (B_zero_tentrix[j] / 100)) break;//精妙的算法

		}
		if (isok == 1) break;
	}
}

void Judge::two_turn(press_pos a, press_pos b, int ** map)
{
	//两个弯
	//这个要写死我了
	//这儿有个小问题，就是one_turn和two_turn需要的零阵不一样
	//所以要先fix一下零阵

	/*先添加A点向左,倒叙*/
	size_fullA = size_A;
	for (int i = a.getx() - 1; i >= 0; --i)
	{
		if (map[i][a.gety()] == 0)
		{
			A_zero_tentrix[size_fullA] = i * 100 + a.gety();//下标从size_A开始
			++size_fullA;
		}
		else break;
	}
	/*不知道要不要排序，先不排了*/
	/*不用排序*/
	/*添加B点向右，正序*/
	size_fullB = size_B;
	for (int i = b.getx() + 1; i < Map::get_mapsize() + 2; ++i)
	{
		if (map[i][b.gety()] == 0)
		{
			B_zero_tentrix[size_fullB] = i * 100 + b.gety();
			++size_fullB;
		}
		else break;
	}

	/*ok，开始我的表演*/
	/*先从水平方向看吧*/
	/*注意ai，bi都是零阵中的下标，要转化成map的坐标才能比较*/
	bool depression = 0;//算法优化，如果配对上了，却中间有非0，则可以break了，这叫希望之后的失望
	for (int ai = horizontal_A; ai < size_fullA; ++ai)
	{
		depression = 0;//充满希望出发
		for (int bi = 0; bi < horizontal_B; ++bi)
		{
			if (A_zero_tentrix[ai] / 100 == B_zero_tentrix[bi] / 100)
			{
				/*反证*/
				isok = 1;
				/*假设成立时的折点*/
				current_salient[0] = 2;
				current_salient[1] = A_zero_tentrix[ai];
				current_salient[2] = B_zero_tentrix[bi];
				for (int j = judge_min(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100)
					+ 1; j < judge_max(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100); ++j)
				{
					if (map[A_zero_tentrix[ai] / 100][j] != 0)
					{
						isok = 0;
						/*假设不成立，只将第一个元素设为-1，作为一个flag*/
						current_salient[0] = -1;
						current_salient[1] = -1;
						current_salient[2] = -1;
						depression = 1;//失望而归
						break;
					}
				}
			}
			if (isok == 1 || depression == 1) break;
		}
		if (isok == 1) break;
		else
		{
			for (int bi = size_B; bi < size_fullB; ++bi)
			{
				if (A_zero_tentrix[ai] / 100 == B_zero_tentrix[bi] / 100)
				{
					/*反证*/
					isok = 1;
					/*假设成立时的折点*/
					current_salient[0] = 2;
					current_salient[1] = A_zero_tentrix[ai];
					current_salient[2] = B_zero_tentrix[bi];
					for (int j = judge_min(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100)
						+ 1; j < judge_max(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100); ++j)
					{
						if (map[A_zero_tentrix[ai] / 100][j] != 0)
						{
							isok = 0;
							/*假设不成立，只将第一个元素设为-1，作为一个flag*/
							current_salient[0] = -1;
							current_salient[1] = -1;
							current_salient[2] = -1;
							depression = 1;
							break;
						}
					}
					if (isok == 1 || depression == 1) break;
				}
			}
		}
		if (isok == 1) break;
	}

	/*再来看竖直的*/
	if (isok == 0)
	{
		for (int aj = 0; aj < horizontal_A; ++aj)
		{
			depression = 0;//带着希望出发
			for (int bj = horizontal_B; bj < size_B; ++bj)
			{
				if (A_zero_tentrix[aj] % 100 == B_zero_tentrix[bj] % 100)
				{
					/*反证*/
					isok = 1;
					/*假设成立时的折点*/
					current_salient[0] = 2;
					current_salient[1] = A_zero_tentrix[aj];
					current_salient[2] = B_zero_tentrix[bj];
					for (int i = A_zero_tentrix[aj] / 100 + 1; i < B_zero_tentrix[bj] / 100; ++i)
					{
						if (map[i][A_zero_tentrix[aj] % 100] != 0)
						{
							isok = 0;
							current_salient[0] = -1;
							current_salient[1] = -1;
							current_salient[2] = -1;
							depression = 1;
							break;
						}
					}
					if (isok == 1 || depression == 1) break;
				}
			}
			if (isok == 1) break;
		}
	}
}

void Judge::find_a_tentrix(press_pos a, int ** map)
{
	int qff = 0;
	/*这个是a点向上的，所以是倒序*/
	for (int j = a.gety() - 1; j >= 0; --j)
	{
		if (map[a.getx()][j] == 0)
		{
			A_zero_tentrix[qff] = a.getx() * 100 + j;
			++qff;
		}
		else break;
	}
	/*排个序*/
	/*因为他是分段连续的所以我可以利用这个性质偷懒*/
	int temp_min = A_zero_tentrix[qff - 1];//这个qff已经不是原来的qff了hhhhhh
	for (int i = 0; i < qff; i++)
	{
		A_zero_tentrix[i] = temp_min + i;
	}

	/*这个是A点向下的*/
	for (int j = a.gety() + 1; j < Map::get_mapsize() + 2; ++j)
	{
		if (map[a.getx()][j] == 0)
		{
			A_zero_tentrix[qff] = a.getx() * 100 + j;
			++qff;
		}
		else break;
	}
	horizontal_A = qff;
	/*这个是A点向右的*/
	for (int i = a.getx() + 1; i < Map::get_mapsize() + 2; ++i)
	{
		if (map[i][a.gety()] == 0)
		{
			A_zero_tentrix[qff] = i * 100 + a.gety();
			++qff;
		}
		else break;
	}
	size_A = qff;
}

void Judge::find_b_tentrix(press_pos a, int ** map)
{
	int qff = 0;
	/*这个是b点向左的，所以是倒序*/
	for (int i = a.getx() - 1; i >= 0; --i)
	{
		if (map[i][a.gety()] == 0)
		{
			B_zero_tentrix[qff] = i * 100 + a.gety();
			++qff;
		}
		else break;
	}
	horizontal_B = qff;//左段范围为[0,horizontal_B_left-1]
					   /*分段连续，我再偷懒,jy排序大法，注意这里是十位数的连续*/
	int temp_min = B_zero_tentrix[qff - 1];
	for (int i = 0; i < qff; ++i)
	{
		B_zero_tentrix[i] = temp_min + i * 100;
	}
	//因为分段连续，所以先把第二段开头qff存下来,好了它已经是成员horizontal_B_left了
	/*这个是b点向上的，倒序*/
	for (int j = a.gety() - 1; j >= 0; --j)
	{
		if (map[a.getx()][j] == 0)
		{
			B_zero_tentrix[qff] = a.getx() * 100 + j;
			++qff;
		}
		else break;
	}
	/*jy排序法*/
	temp_min = B_zero_tentrix[qff - 1];
	for (int i = horizontal_B; i < qff; i++)
	{
		B_zero_tentrix[i] = temp_min + i - horizontal_B;
	}

	/*这个是b点向下的*/
	for (int j = a.gety() + 1; j < Map::get_mapsize() + 2; ++j)
	{
		if (map[a.getx()][j] == 0)
		{
			B_zero_tentrix[qff] = a.getx() * 100 + j;
			++qff;
		}
		else break;
	}
	size_B = qff;
}

void Judge::secret_weapon(press_pos a, press_pos b, int ** map)
{
	//delete[]A_zero_tentrix;
	//delete[]B_zero_tentrix;
	/*内存泄漏吗*/
	A_zero_tentrix = new int[Map::get_mapsize() * 2 + 2];
	B_zero_tentrix = new int[Map::get_mapsize() * 2 + 2];
	find_a_tentrix(a, map);
	find_b_tentrix(b, map);
}

bool Judge::get_isok()
{
	return isok;
}

int Judge::judge_min(int x, int y)
{
	return (x<=y)?x:y;
}

int Judge::judge_max(int x, int y)
{
	return (x>=y)?x:y;
}

Judge::Judge()
{
	current_salient = new int[5];
	for (int i = 1; i < 5; i++)
	{
		current_salient[i] = 0;
	}
}


Judge::~Judge()
{
	delete[]A_zero_tentrix;
	delete[]B_zero_tentrix;
}
