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
	/*�����ڶ�������Ϊ�Ƿ�Ϊ�ط�ģʽ��0��Ϊ�񣬷�0��Ϊ�طŵ�level*/
	~GameWidget();
	int bomb_num;//ը����
	int promp_num;//��ʾ��
	int level;//��¼�ؿ���
	int scores;//�ܷ���
	int temp_time;//ʣ��ʱ��
	
protected:
	void paintEvent(QPaintEvent *);
	
private:
	QPushButton * **button_arr;//ͼ�갴ť����
	QPushButton *stop;//��ͣ��ť
	QPushButton *prompt;//��ʾ����
	QPushButton *bomb;//ը��
	QPushButton *save;//�浵
	QButtonGroup*BGM_Group;//�������ְ�ť��
	
	QMediaPlayer *player;//�������ֲ�����
	QMediaPlayer *player2;//����˵��������
	QMediaPlayer *player3;//��Ч�����������ߺ�ը������Ч��
	QTimer *timer;//��ͨ��ʱ
	QTimer *timer2;//�طż�ʱ
	QProgressBar *progress;//������

	QFont ft;//����

	QSignalMapper* signalMapper;//�൱��һ���ź�վ��������ĵ�λ����Ϣ���͸�get..pos

	QLabel *properties;//��ʾ��������

	/*�Լ�����*/
	Map mymap;//���ֵ�ͼ
	press_pos posA;//�����A��
	press_pos posB;//�����B��
	Judge judge;//����ͬ־
	Recorder recorder;//����ͬ־
	AI ai;//�˹�����


	void add_icon(int i, int j);//�����ֵ�ͼ��ʾ������ͬ���ֱ�ɲ�ͬͼ��
	void update_the_map();//���µ�ͼ
	void visual_generate();//��ͼ������һ��
	void go_to_next_level();//ȥ��һ�ص��ܵ��Ⱥ���
	void property_manager();//������������
	QLineF convert_line(int i1, int j1, int i2, int j2);//�����õĸ�������

	
	bool use_bomb;//�Ƿ�ʹ��ը��
	int rep;//�Ƿ��ǻط�ģʽ
	int last_actiontime;//��¼�ϴζ�����ʱ�䣬����30s������������
	QString skin;//����Ƥ��

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