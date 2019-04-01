#include "link_game.h"

link_game::link_game(QWidget *parent)
	: QMainWindow(parent),skin_num("1"),speedx(5),speedy(3),adx(10),ady(10)
{
	/*set of the main window*/

	this->resize(640, 480);//set the window size
	this->setWindowIcon(QIcon("img1/icon.png"));//set icon of the file
	this->setWindowTitle(tr("hello"));//set the title

	/*sth about background*/

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap("img1/back.jpg").scaled(this->size())));
	this->setPalette(palette);

	/*sth about label*/
	label = new QLabel(this);
	label->setText("Author : JY    Version : 2.0    email : 3534679530@qq.com");
	label->setGeometry(20, 20, 640, 20);
	QFont font;
	font.setPointSize(12);
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::green);
	label->setFont(font);
	label->setPalette(pa);
	
	/*advertisement*/
	ad = new QLabel(this);
	ad->setText("Jy is so handsome!");
	font.setPointSize(14);
	pa.setColor(QPalette::WindowText, Qt::red);
	ad->setFont(font);
	ad->setPalette(pa);
	clock = new QTimer(this);
	clock->setInterval(50);
	clock->start();
	connect(clock, SIGNAL(timeout()), this, SLOT(ad_run()));

	/*set of button*/
	
	startbtn = new QPushButton("start", this);//the start button
	//startbtn->setIcon(QIcon("img/what.jpg"));//add an icon for the startbutton
	//startbtn->setIconSize(QSize(80, 80));//resize the button
	startbtn->setGeometry(QRect(280, 90, 60, 50));//set the coordinate of startbutton
	//startbtn->setFlat(true);//set the flat

	exitbtn = new QPushButton("exit", this);//the exit button
	//startbtn->setIcon(QIcon("img/what.jpg"));//add an icon for the exit button
	//startbtn->setIconSize(QSize(80, 80));//resize the button
	exitbtn->setGeometry(QRect(280, 340, 60, 50));//set the coordinate of exitbutton
	//exitbtn->setFlat(true);//set the flat

	helpbtn = new QPushButton("help", this);//the help button
	//startbtn->setIcon(QIcon("img/what.jpg"));//add an icon for the help button
	//startbtn->setIconSize(QSize(80, 80));//resize the button
	helpbtn->setGeometry(QRect(280, 290, 60, 50));//set the coordinate of helpbutton
	//helpbtn->setFlat(true);//set the flat

	compete = new QPushButton("computer", this);
	compete->setGeometry(QRect(280, 140, 60, 50));
	//compete->setFlat(true);

	read = new QPushButton("read", this);
	read->setGeometry(280, 190, 60, 50);
	//read->setFlat(true);

	replay = new QPushButton("replay", this);
	replay->setGeometry(280, 240, 60, 50);
	//replay->setFlat(true);

	pButtonGroup = new QButtonGroup(this);
	pButtonGroup->setExclusive(true);//设置互斥
	for (int i = 0; i < 2; ++i)
	{
		QRadioButton *skinButton = new QRadioButton(this);
		// 设置文本
		skinButton->setText(QString::fromLocal8Bit("%1").arg(i + 1));
		skinButton->setGeometry(10 + 50 * i, 8, 50, 20);
		pButtonGroup->addButton(skinButton,i+1);
	}
	
	

	this->connect(startbtn, SIGNAL(clicked(bool)), this, SLOT(startbtn_click()));
	this->connect(exitbtn, SIGNAL(clicked(bool)), this, SLOT(close()));
	this->connect(helpbtn, SIGNAL(clicked(bool)), this, SLOT(helpbtn_click()));
	this->connect(compete, SIGNAL(clicked(bool)), this, SLOT(compete_click()));
	this->connect(read, SIGNAL(clicked(bool)), this, SLOT(read_click()));
	this->connect(replay, SIGNAL(clicked(bool)), this, SLOT(replay_click()));
	this->connect(pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(skin_click(QAbstractButton*)));
}

link_game::~link_game()
{
}

void link_game::startbtn_click()
{
	game = new GameWidget(this,skin_num);
	game->show();
}

void link_game::helpbtn_click()
{
	QProcess* process = new QProcess();
	QString notepadPath = "notepad.exe help.txt";
	process->start(notepadPath);
}

void link_game::compete_click()
{
	QProcess* process = new QProcess();
	QString sb_computer = "computer.exe";
	process->start(sb_computer);
	game = new GameWidget(this,skin_num);
	game->show();
}

void link_game::read_click()
{
	int n = 0;
	QInputDialog d(this);
	d.setWindowTitle("inputing");
	d.setLabelText("please input your password");
	d.setInputMode(QInputDialog::IntInput);  //TextInput输入文本，DoubleInput输入double类型
	if (d.exec() == QInputDialog::Accepted)
		n = d.intValue();           //TextValue、doubleValue
	int temp_time;
	int scores;
	int level;
	int promp_num;
	int bomb_num;
	reader.read_map(map2, temp_time, scores, level, promp_num, bomb_num,0,n);
	//最后一个参数是第几个map，可以在这里搞交互界面
	game = new GameWidget(this, skin_num, map2, temp_time, scores, level, promp_num, bomb_num,0,temp_time);
	game->show();
}

void link_game::replay_click()
{
	int n = 0;
	QInputDialog d(this);
	d.setWindowTitle("inputing");
	d.setLabelText("please input the level");
	d.setInputMode(QInputDialog::IntInput);  //TextInput输入文本，DoubleInput输入double类型
	if (d.exec() == QInputDialog::Accepted)
		n = d.intValue();           //TextValue、doubleValue
	int temp_time;
	int scores;
	int level;
	int promp_num;
	int bomb_num;
	reader.read_map(map2, temp_time, scores, level, promp_num, bomb_num, 1, n);
	//最后一个参数是第几个map，可以在这里搞交互界面
	game = new GameWidget(this, skin_num, map2, temp_time, scores, level, promp_num, bomb_num,n);
	game->show();
}

void link_game::skin_click(QAbstractButton *)
{
	skin_num = QString::number(pButtonGroup->checkedId());
}

void link_game::ad_run()
{
	if (adx >= 440 || adx <= 0) speedx *= -1;
	if (ady >= 460 || ady <= 0) speedy *= -1;
	adx += speedx;
	ady += speedy;
	ad->setGeometry(adx, ady, 200, 20);
}
