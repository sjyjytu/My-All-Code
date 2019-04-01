#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include <qwidget.h>
#include <qprogressbar.h>
#include <qicon.h>
#include <qpalette.h>
#include <qbrush.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qpainter.h>
#include <qpen.h>
#include <qline.h>
#include <qimage.h>
#include <qtimer.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qfont.h>
#include <qinputdialog.h>
#include <qsignalmapper.h>
#include <qsize.h>
#include <qinputdialog.h>
#include <QtMultimedia/qmediaplayer.h>
#include <qurl.h>
#include <qlayout.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlist.h>

#include<vector>
#include<algorithm>

#include "Recorder.h"
#include "AI.h"

class GameWidget:public QWidget
{
	Q_OBJECT
public:
	explicit GameWidget(QWidget *parent = 0, QString skin = "1",Map &MAP = Map(), int tt=100,int sc=0,int lv=1,int pn=3,int bn=3, int rp = 0, int last_act = 100);
	/*倒数第二个参数为是否为回放模式，0则为否，非0则为回放的level*/
	~GameWidget();
	int bomb_num;//炸弹数
	int promp_num;//提示数
	int level;//记录关卡数
	int scores;//总分数
	int temp_time;//剩余时间
	
protected:
	void paintEvent(QPaintEvent *);
	
private:
	QPushButton * **button_arr;//图标按钮数组
	QPushButton *stop;//暂停按钮
	QPushButton *prompt;//提示功能
	QPushButton *bomb;//炸弹
	QPushButton *save;//存档
	QButtonGroup*BGM_Group;//背景音乐按钮组
	
	QMediaPlayer *player;//背景音乐播放器
	QMediaPlayer *player2;//机器说话播放器
	QMediaPlayer *player3;//音效播放器（连线和炸弹的音效）
	QTimer *timer;//普通计时
	QTimer *timer2;//回放计时
	QProgressBar *progress;//进度条

	QFont ft;//字体

	QSignalMapper* signalMapper;//相当于一个信号站，将点击的点位置信息传送给get..pos

	QLabel *properties;//显示道具数量

	/*自己的类*/
	Map mymap;//数字地图
	press_pos posA;//点击的A点
	press_pos posB;//点击的B点
	Judge judge;//法官同志
	Recorder recorder;//记者同志
	AI ai;//人工智障


	void add_icon(int i, int j);//将数字地图显示化，不同数字变成不同图标
	void update_the_map();//更新地图
	void visual_generate();//地图进入下一关
	void go_to_next_level();//去下一关的总调度函数
	void property_manager();//道具数量管理
	QLineF convert_line(int i1, int j1, int i2, int j2);//连线用的辅助函数

	
	bool use_bomb;//是否使用炸弹
	int rep;//是否是回放模式
	int last_actiontime;//记录上次动作的时间，用于30s不动作则判输
	QString skin;//哪种皮肤

public slots:
	void timeroutslot();//decrease every second
	void REPLAY();
	void stop_click();
	void prompt_click();
	void get_the_press_pos(int);
	void bomb_click();
	void save_click();
	void onButtonClicked(QAbstractButton *button);
};

#endif