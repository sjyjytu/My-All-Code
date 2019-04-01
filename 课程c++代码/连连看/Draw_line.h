#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include <qpainter.h>
#include <qpen.h>
#include <qline.h>
#include <qwidget.h>
#include "Press_pos.h"

class Draw_line
{
private:
	QPainter *painter;
public:
	Draw_line(QWidget *parent = 0);
	~Draw_line();
	QLineF convert_line(int i1, int j1, int i2, int j2);
	void draw_line(int pattern,int current_salient[3],press_pos A, press_pos B,bool is_swap);

};

#endif // !DRAW_LINE_H]