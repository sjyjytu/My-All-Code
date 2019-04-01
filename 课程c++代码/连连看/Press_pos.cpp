#include "press_pos.h"



press_pos::press_pos(int a,int b):x(a),y(b)
{

}


press_pos::~press_pos()
{
}

void press_pos::set_pos(int a, int b)
{
	x = a;
	y = b;
}

bool press_pos::operator==(const press_pos & pos1) const
{
	return x == pos1.x && y == pos1.y;
}

bool press_pos::operator!=(const press_pos & pos1) const
{
	return x != pos1.x || y != pos1.y;
}

const int press_pos::getx()
{
	return x;
}

const int press_pos::gety()
{
	return y;
}
