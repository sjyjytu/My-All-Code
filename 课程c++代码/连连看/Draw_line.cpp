#include "Draw_line.h"



Draw_line::Draw_line(QWidget *parent)
{
	painter->setPen(QPen(Qt::blue, 3));
}


Draw_line::~Draw_line()
{
}

QLineF Draw_line::convert_line(int i1, int j1, int i2, int j2)
{
	/*�߼�������ͼ�λ������ת����ϵ��10 + i * 40, 50 + j * 30*/
	/*ͼ�λ������뻭�ߵ㣨��ť���ģ�����ת����ϵ��+20��+15*/
	return QLineF(10 + 40 * i1 + 20, 50 + 30 * j1 + 15, 10 + 40 * i2 + 20, 50 + 30 * j2 + 15);
}

void Draw_line::draw_line(int pattern, int current_salient[3], press_pos A, press_pos B, bool is_swap)
{
	if (pattern == 0)
	{
		painter->drawLine(convert_line(A.getx(), A.gety(), B.getx(), B.gety()));
	}
	else if (pattern == 1)
	{
		painter->drawLine(convert_line(A.getx(), A.gety(), current_salient[1] / 100, current_salient[1] % 100));
		painter->drawLine(convert_line(current_salient[1] / 100, current_salient[1] % 100, B.getx(), B.gety()));
	}
	else if (pattern == 2)
	{
		if (is_swap)
		{
			painter->drawLine(convert_line(current_salient[1] / 100, current_salient[1] % 100, current_salient[2] / 100, current_salient[2] % 100));
			painter->drawLine(convert_line(A.getx(), A.gety(), current_salient[2] / 100, current_salient[2] % 100));
			painter->drawLine(convert_line(current_salient[1] / 100, current_salient[1] % 100, B.getx(), B.gety()));
		}
		else
		{
			painter->drawLine(convert_line(current_salient[1] / 100, current_salient[1] % 100, current_salient[2] / 100, current_salient[2] % 100));
			painter->drawLine(convert_line(B.getx(), B.gety(), current_salient[2] / 100, current_salient[2] % 100));
			painter->drawLine(convert_line(current_salient[1] / 100, current_salient[1] % 100, A.getx(), A.gety()));
		}
	}
}
