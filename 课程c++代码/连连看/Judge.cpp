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
	/*������������ĺ���*/
	/*��is_ok����*/
	isok = 0;
	/*�Ȱ�a b����������ж�λ�ã����ο�д��������*/
	aleft_bright(a, b);
	/*Ȼ��ѿ��ܽ�������a b����current_salient��*/
	current_salient[3] = a.getx() * 100 + a.gety();
	current_salient[4] = b.getx() * 100 + b.gety();
	//�ж��Ƿ�ͬһ��ͼ����
	if (map[a.getx()][a.gety()] == map[b.getx()][b.gety()])
	{
		/*�ж�����·��������4�����һ��ֻ���ܳ���һ��*/
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
	//�����䣬�����ں���ֱ�ߺ�ֱ������,����ǰ�᣺����������������
	if (a.getx() == b.getx())
	{
		//����B4����ֱ���
		isok = 1;//�÷�֤�����ȼ�������ͨ·
		/*�������ʱ�ĵ�һ��Ԫ��Ϊ0*/
		current_salient[0] = 0;
		for (int i = 1; i < b.gety() - a.gety(); i++)
		{
			if (map[a.getx()][a.gety() + i] != 0)
			{
				//���費����
				isok = 0;
				current_salient[0] = -1;
				break;
			};
		}
	}
	else if (a.gety() == b.gety())
	{
		//����B2��ˮƽ���
		isok = 1;//�÷��������ȼ�������ͨ·
		current_salient[0] = 0;
		//if (b.getx()-a.getx()==1) 
		for (int i = 1; i < b.getx() - a.getx(); i++)
		{
			if (map[a.getx() + i][a.gety()] != 0)
			{
				//���費����
				isok = 0;
				current_salient[0] = -1;
				break;
			};
		}

	}
}

void Judge::one_turn()
{
	//һ����
	//�㷨�ǰ�A��ʮ����0���B��ʮ�������������������A�����󣬿���B���������޽���
	//�Һ����޷�֪������Ĵ�С��������զ�죡
	//���� �һ����˷ѿռ���ˡ�����
	if (A_zero_tentrix[size_A - 1] / 100 < B_zero_tentrix[size_B - 1] / 100 &&
		B_zero_tentrix[0] / 100 > A_zero_tentrix[0] / 100) return;//�϶�û�н���
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
			else if ((A_zero_tentrix[i] / 100) < (B_zero_tentrix[j] / 100)) break;//������㷨

		}
		if (isok == 1) break;
	}
}

void Judge::two_turn(press_pos a, press_pos b, int ** map)
{
	//������
	//���Ҫд������
	//����и�С���⣬����one_turn��two_turn��Ҫ������һ��
	//����Ҫ��fixһ������

	/*�����A������,����*/
	size_fullA = size_A;
	for (int i = a.getx() - 1; i >= 0; --i)
	{
		if (map[i][a.gety()] == 0)
		{
			A_zero_tentrix[size_fullA] = i * 100 + a.gety();//�±��size_A��ʼ
			++size_fullA;
		}
		else break;
	}
	/*��֪��Ҫ��Ҫ�����Ȳ�����*/
	/*��������*/
	/*���B�����ң�����*/
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

	/*ok����ʼ�ҵı���*/
	/*�ȴ�ˮƽ���򿴰�*/
	/*ע��ai��bi���������е��±꣬Ҫת����map��������ܱȽ�*/
	bool depression = 0;//�㷨�Ż������������ˣ�ȴ�м��з�0�������break�ˣ����ϣ��֮���ʧ��
	for (int ai = horizontal_A; ai < size_fullA; ++ai)
	{
		depression = 0;//����ϣ������
		for (int bi = 0; bi < horizontal_B; ++bi)
		{
			if (A_zero_tentrix[ai] / 100 == B_zero_tentrix[bi] / 100)
			{
				/*��֤*/
				isok = 1;
				/*�������ʱ���۵�*/
				current_salient[0] = 2;
				current_salient[1] = A_zero_tentrix[ai];
				current_salient[2] = B_zero_tentrix[bi];
				for (int j = judge_min(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100)
					+ 1; j < judge_max(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100); ++j)
				{
					if (map[A_zero_tentrix[ai] / 100][j] != 0)
					{
						isok = 0;
						/*���費������ֻ����һ��Ԫ����Ϊ-1����Ϊһ��flag*/
						current_salient[0] = -1;
						current_salient[1] = -1;
						current_salient[2] = -1;
						depression = 1;//ʧ������
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
					/*��֤*/
					isok = 1;
					/*�������ʱ���۵�*/
					current_salient[0] = 2;
					current_salient[1] = A_zero_tentrix[ai];
					current_salient[2] = B_zero_tentrix[bi];
					for (int j = judge_min(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100)
						+ 1; j < judge_max(A_zero_tentrix[ai] % 100, B_zero_tentrix[bi] % 100); ++j)
					{
						if (map[A_zero_tentrix[ai] / 100][j] != 0)
						{
							isok = 0;
							/*���費������ֻ����һ��Ԫ����Ϊ-1����Ϊһ��flag*/
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

	/*��������ֱ��*/
	if (isok == 0)
	{
		for (int aj = 0; aj < horizontal_A; ++aj)
		{
			depression = 0;//����ϣ������
			for (int bj = horizontal_B; bj < size_B; ++bj)
			{
				if (A_zero_tentrix[aj] % 100 == B_zero_tentrix[bj] % 100)
				{
					/*��֤*/
					isok = 1;
					/*�������ʱ���۵�*/
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
	/*�����a�����ϵģ������ǵ���*/
	for (int j = a.gety() - 1; j >= 0; --j)
	{
		if (map[a.getx()][j] == 0)
		{
			A_zero_tentrix[qff] = a.getx() * 100 + j;
			++qff;
		}
		else break;
	}
	/*�Ÿ���*/
	/*��Ϊ���Ƿֶ������������ҿ��������������͵��*/
	int temp_min = A_zero_tentrix[qff - 1];//���qff�Ѿ�����ԭ����qff��hhhhhh
	for (int i = 0; i < qff; i++)
	{
		A_zero_tentrix[i] = temp_min + i;
	}

	/*�����A�����µ�*/
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
	/*�����A�����ҵ�*/
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
	/*�����b������ģ������ǵ���*/
	for (int i = a.getx() - 1; i >= 0; --i)
	{
		if (map[i][a.gety()] == 0)
		{
			B_zero_tentrix[qff] = i * 100 + a.gety();
			++qff;
		}
		else break;
	}
	horizontal_B = qff;//��η�ΧΪ[0,horizontal_B_left-1]
					   /*�ֶ�����������͵��,jy����󷨣�ע��������ʮλ��������*/
	int temp_min = B_zero_tentrix[qff - 1];
	for (int i = 0; i < qff; ++i)
	{
		B_zero_tentrix[i] = temp_min + i * 100;
	}
	//��Ϊ�ֶ������������Ȱѵڶ��ο�ͷqff������,�������Ѿ��ǳ�Աhorizontal_B_left��
	/*�����b�����ϵģ�����*/
	for (int j = a.gety() - 1; j >= 0; --j)
	{
		if (map[a.getx()][j] == 0)
		{
			B_zero_tentrix[qff] = a.getx() * 100 + j;
			++qff;
		}
		else break;
	}
	/*jy����*/
	temp_min = B_zero_tentrix[qff - 1];
	for (int i = horizontal_B; i < qff; i++)
	{
		B_zero_tentrix[i] = temp_min + i - horizontal_B;
	}

	/*�����b�����µ�*/
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
	/*�ڴ�й©��*/
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
