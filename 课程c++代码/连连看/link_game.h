#ifndef LINK_GAME_H
#define LINK_GAME_H

#include <QtWidgets/QMainWindow>
#include <QIcon>
#include <qpalette.h>
#include <qbrush.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qprocess.h>
#include <qinputdialog.h>
#include "GameWidget.h"

class link_game : public QMainWindow
{
	Q_OBJECT

public:
	link_game(QWidget *parent = Q_NULLPTR);
	~link_game();
	
private:
	QPushButton * startbtn;
	QPushButton *exitbtn;
	QPushButton *helpbtn;
	QPushButton *compete;
	QPushButton *replay;
	QButtonGroup*pButtonGroup;//choose skin
	GameWidget *game;
	QLabel *label;
	QLabel *ad;
	QTimer *clock;
	QPushButton *read;//读档
	Recorder reader;
	Map map2;
	QString skin_num;
	int speedx;//广告的速度
	int speedy;
	int adx;//广告的坐标
	int ady;

public slots:
	void startbtn_click();
	void helpbtn_click();
	void compete_click();
	void read_click();
	void replay_click();
	void skin_click(QAbstractButton*);
	void ad_run();
};
#endif // !LINK_GAME_H