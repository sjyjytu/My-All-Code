#include "GameWidget.h"

GameWidget::GameWidget(QWidget*parent, QString skin,Map &MAP,int tt,int sc,int lv,int pn, int bn,int rp, int last_act)
	:QWidget(parent), mymap(MAP),temp_time(tt), button_arr(NULL),use_bomb(0),bomb_num(bn),promp_num(pn),level(lv),scores(sc),rep(rp), last_actiontime(last_act), skin(skin)
{
	this->setAutoFillBackground(true);//cover the parent widget
	this->resize(640, 480);
	
	/*button*/
	stop = new QPushButton("stop", this);
	stop->setGeometry(530, 320, 100, 30);
	connect(stop, SIGNAL(clicked(bool)), this, SLOT(stop_click()));

	prompt = new QPushButton("prompt", this);
	prompt->setGeometry(530, 360, 100, 30);
	connect(prompt, SIGNAL(clicked(bool)), this, SLOT(prompt_click()));

	bomb = new QPushButton("bomb", this);
	bomb->setGeometry(530, 400, 100, 30);
	connect(bomb, SIGNAL(clicked(bool)), this, SLOT(bomb_click()));

	save = new QPushButton("save", this);
	save->setGeometry(530, 280, 100, 30);
	connect(save, SIGNAL(clicked(bool)), this, SLOT(save_click()));

	/*bgm choose button*/
	BGM_Group = new QButtonGroup(this);
	BGM_Group->setExclusive(true);//设置互斥
	for (int i = 0; i < 3; ++i)
	{
		QRadioButton *pButton = new QRadioButton(this);

		// 设置文本
		pButton->setText(QString::fromLocal8Bit("bgm%1").arg(i + 1));
		pButton->setGeometry(10 + 50 * i, 8, 50, 20);
		BGM_Group->addButton(pButton);
	}
	//连接信号槽
	connect(BGM_Group, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

	/*players*/
	player = new QMediaPlayer();
	player2 = new QMediaPlayer();
	player3 = new QMediaPlayer();
	player->setVolume(50);
	player2->setVolume(100);
	player3->setVolume(70);
	/*create a button array to represent the icons and signalmap them to get_press_pos*/
	visual_generate();

	/*about time*/
	timer = new QTimer(this);
	timer->setInterval(1000);
	if (!rep) timer->start();//如果不是回放模式，就计时
	timer2 = new QTimer(this);
	timer2->setInterval(900);
	if (rep) timer2->start();//如果是回放模式，就开始计时

	progress = new QProgressBar(this);
	progress->setStyleSheet("\
                              QProgressBar::chunk {\
                                  background-color: #CD96CD;\
                                  width: 10px;\
                                  margin: 0.5px;\
                              }");
	progress->setRange(0, 100);
	progress->setValue(temp_time);
	progress->setGeometry(250, 8, 300, 21);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeroutslot()));
	connect(timer2, SIGNAL(timeout()), this, SLOT(REPLAY()));

	/*显示道具数,乱入一个关卡数*/
	properties = new QLabel(this);
	properties->setText("promp:" + QString::number(promp_num) +
						"   bomb:" + QString::number(bomb_num) +
						"                    level:" + QString::number(level) +
						"           scores:" + QString::number(scores));
	properties -> setGeometry(10, 30, 640, 20);
	/*字体*/
	ft.setPointSize(12);
	properties->setFont(ft);
	
}


GameWidget::~GameWidget()
{

}

void GameWidget::paintEvent(QPaintEvent *)
{
	int this_five[5];//这五个操作数
	if (rep)
	{
		for (int i = 0; i < 5; i++)
		{
			this_five[i] = recorder.operations[i];
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			this_five[i] =judge.current_salient[i];
		}
	}
	if ((judge.get_isok()&&(!rep))||rep)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::blue, 3));
		if (this_five[0] == 0)
		{
			painter.drawLine(convert_line(this_five[3] / 100, this_five[3] % 100, this_five[4] / 100, this_five[4] % 100));
		}
		else if (this_five[0] == 1)
		{
			painter.drawLine(convert_line(this_five[3] / 100, this_five[3] % 100, this_five[1] / 100, this_five[1] % 100));
			painter.drawLine(convert_line(this_five[1] / 100, this_five[1] % 100, this_five[4] / 100, this_five[4] % 100));
		}
		else if (this_five[0] == 2)
		{
			painter.drawLine(convert_line(this_five[1] / 100, this_five[1] % 100, this_five[2] / 100, this_five[2] % 100));
			painter.drawLine(convert_line(this_five[4] / 100, this_five[4] % 100, this_five[2] / 100, this_five[2] % 100));
			painter.drawLine(convert_line(this_five[1] / 100, this_five[1] % 100, this_five[3] / 100, this_five[3] % 100));
		}
	}
}

void GameWidget::add_icon(int i, int j)
{
	int temp = mymap.new_map[i][j];//store the kind of icon
	if (temp == 0) return;//边框无按钮
	/*the full address of the specific icon*/
	QString temp_num = QString::number(temp, 10);
	QString icon_address("img"+skin+"/");
	QString last_name(".jpg");
	icon_address.append(temp_num);
	icon_address.append(last_name);
	QIcon png(icon_address);
	//png.load(icon_address);
	/*make the button_arr*/
	button_arr[i][j] = new QPushButton(/*png, "",*/ this);//add icon to the button
	button_arr[i][j]->setIcon(png);
	button_arr[i][j]->setIconSize(QSize(30,50));
	button_arr[i][j]->setGeometry(10 + i * 40, 50 + j * 30, 40, 30);//set the visual position
	button_arr[i][j]->show();//致命之错啊！
	/*connect each element to the signalMapper, in order to send i and j.*/
	connect(button_arr[i][j], SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button_arr[i][j], i * 100 + j);
}

void GameWidget::update_the_map()
{
	/*更新炸弹和提示*/
	property_manager();

	/*更新box*/
	int num = mymap.new_map[posA.getx()][posA.gety()] - 1;
	std::vector<int>::iterator iter = std::find(mymap.box[num].begin(), mymap.box[num].end(), posA.getx() * 100 + posA.gety());
	if (iter != mymap.box[num].end()) mymap.box[num].erase(iter);
	/*先删一个再删另一个，否则怕出问题*/
	iter = std::find(mymap.box[num].begin(), mymap.box[num].end(), posB.getx() * 100 + posB.gety());
	if (iter != mymap.box[num].end()) mymap.box[num].erase(iter);
	
	/*在new_map上置零*/
	mymap.new_map[posA.getx()][posA.gety()] = 0;
	mymap.new_map[posB.getx()][posB.gety()] = 0;
	
	/*连线*/
	repaint();
	//draw.draw_line(judge.current_salient[0], judge.current_salient,posA,posB,judge.is_swap);
	/*图形化界面隐藏按钮*/
	button_arr[posA.getx()][posA.gety()]->hide();
	button_arr[posB.getx()][posB.gety()]->hide();
}

void GameWidget::visual_generate()
{
	signalMapper = new QSignalMapper(this);//create an intermediary
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(get_the_press_pos(int)));

	button_arr = new QPushButton**[Map::get_mapsize() + 2];

	for (int i = 0; i < Map::get_mapsize() + 2; i++)
	{
		button_arr[i] = new QPushButton*[Map::get_mapsize() + 2];
		for (int j = 0; j < Map::get_mapsize() + 2; j++)
		{
			add_icon(i, j);
		}
	}
	/*如果不是在回放，那就每一关都录下来。顺便把该level的operation.txt清空一下*/
	if (!rep)
	{
		recorder.save_now(mymap, temp_time, scores, level, promp_num, bomb_num, 1, level);
		recorder.clear_operation(level);
	}
}

void GameWidget::go_to_next_level()
{
	/*关卡数+1*/
	level += 1;
	/*根据剩余时间奖励炸弹和提示*/
	promp_num += temp_time / 20;
	bomb_num += temp_time / 30;
	property_manager();
	
	/*最多能承受12*12的地图*/
	if (Map::get_mapsize() < 12)
	{
		/*增加难度,重新开始*/
		Map::set_mapsize(Map::get_mapsize() + 2);
		temp_time = 100 - 3*level;//这个可以减少或增加一些
	}
	else temp_time = 100 - 3*level;
	last_actiontime = temp_time;
	/*开始计时*/
	progress->setValue(temp_time);
	timer->start();
	mymap.left_icon = Map::get_mapsize() * Map::get_mapsize() / 2;
	mymap.generate_map();
	visual_generate();
	this->show();
}

void GameWidget::property_manager()
{
	properties->setText("promp:" + QString::number(promp_num) + 
						"   bomb:" + QString::number(bomb_num) + 
						"                    level:" + QString::number(level) + 
						"           scores:" + QString::number(scores));
	if (promp_num == 0)
	{
		prompt->setEnabled(false);
	}
	else
	{
		prompt->setEnabled(true);
	}
	if (bomb_num == 0)
	{
		use_bomb = 0;
		bomb->setEnabled(false);
		bomb->setText("no bomb!");
	}
	else
	{
		bomb->setEnabled(true);
		bomb->setText("use me!!!");
	}
}

QLineF GameWidget::convert_line(int i1, int j1, int i2, int j2)
{
	return QLineF(10 + 40 * i1 + 20, 50 + 30 * j1 + 15, 10 + 40 * i2 + 20, 50 + 30 * j2 + 15);
}

void GameWidget::REPLAY()
{
	/*每一次都从operation(n).txt读五个元素*/
	recorder.read_oper(rep);//注意参数n
	if (recorder.operations == NULL)
	{
		QMessageBox::warning(this, "over", "Game Over!", QMessageBox::Ok);
		if (QMessageBox::Ok)
		{
			this->close();
		}
	}
	button_arr[recorder.operations[3] / 100][recorder.operations[3] % 100]->hide();
	button_arr[recorder.operations[4] / 100][recorder.operations[4] % 100]->hide();
	if (recorder.operations[0] != -1)
	{
		/*没有使用炸弹*/
		repaint();
	}
}

void GameWidget::stop_click()
{
	timer->stop();
	player->stop();
	QMessageBox::warning(this, "Stop", "Game Stop!", QMessageBox::Ok);
	if (QMessageBox::Ok)
	{
		timer->start();
		player->play();
	}
}

void GameWidget::timeroutslot()
{
	--temp_time;
	progress->setValue(temp_time);
	if (temp_time == 30)
	{
		player2->setMedia(QUrl::fromLocalFile("music/action2.mp3"));
		player2->play();
	}
	if (last_actiontime - temp_time > 10)
	{
		player2->setMedia(QUrl::fromLocalFile("music/quick.mp3"));
		player2->play();
	}
	if (temp_time == 0||(last_actiontime-temp_time>20))//超时判输
	{
		timer->stop();
		player->stop();
		player2->setMedia(QUrl::fromLocalFile("music/notime.mp3"));
		player2->play();
		QMessageBox::warning(this, "omg", "YOU Lose!",QMessageBox::Ok);
		if (QMessageBox::Ok)
		{
			this->close();
			player->stop();
		}
	}
}

void GameWidget::prompt_click()
{
	/*先把posA，posB置零*/
	posA = press_pos(0, 0);
	posB = press_pos(0, 0);
	/*用ai找点*/
	ai.ai_find(mymap, judge);
	/*若找到了，模拟点击两个点*/
	if (ai.get_findit())
	{
		/*提示数减1*/
		promp_num--;
		/*模拟点击*/
		get_the_press_pos(ai.get_posk1());
		get_the_press_pos(ai.get_posk2());
	}
}

void GameWidget::bomb_click()
{
	if (!use_bomb)
	{
		use_bomb = 1;
		bomb->setText("using...");
		bomb->setStyleSheet("color:red");
	}
	else
	{
		use_bomb = 0;
		bomb->setText("use me!!!");
		bomb->setStyleSheet("color:black");
	}
}

void GameWidget::save_click()
{
	timer->stop();
	int n = 0;
	QInputDialog d(this);
	d.setWindowTitle("inputing");
	d.setLabelText("please input a password");
	d.setInputMode(QInputDialog::IntInput);  //TextInput输入文本，DoubleInput输入double类型
	if (d.exec() == QInputDialog::Accepted)
		n = d.intValue();           //TextValue、doubleValue
	/*注意最后一个参数要改*/
	recorder.save_now(mymap,temp_time,scores,level,promp_num,bomb_num,0,n);
	QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Success!", "Do you want to continue?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if (rb == QMessageBox::Yes)
	{
		timer->start();
	}
	else
	{
		this->close();
	}
}

void GameWidget::onButtonClicked(QAbstractButton * button)
{
	player->stop();
	QList<QAbstractButton*> list = BGM_Group->buttons();
	foreach(QAbstractButton *pButton, list)
	{
		if (pButton->isChecked())
		{
			player->setMedia(QUrl::fromLocalFile("music/" + button->text() + ".mp3"));
		}
	}
	player->play();
}

void GameWidget::get_the_press_pos(int k)
{
	/*because k = i*100+j*/
	int i = k / 100;
	int j = k % 100;

	/*if the press button is not null, give it to posA or posB,
	depending on whether posA is null*/
	if (posA.getx() == 0 && posA.gety() == 0) posA = press_pos(i, j);
	else if (posA != press_pos(i, j))//ensure that they are not the same points
	{
		posB = press_pos(i, j);
		judge.have_a_judge(posA, posB, mymap.new_map);
		if (judge.get_isok()||use_bomb)//给炸弹兄条通路
		{
			last_actiontime = temp_time;//记录本次时间，用于检测是否超时
			scores += mymap.create_randnum(15, 3) * 3;//加分，有一定的随机性
			/*如果使用了炸弹，则炸弹数减1*/
			if (use_bomb)
			{
				bomb_num--;
				player3->setMedia(QUrl::fromLocalFile("music/bomb.mp3"));
				player3->play();
			}
			else
			{
				/*放个音效*/
				player3->setMedia(QUrl::fromLocalFile("music/ding.mp3"));
				player3->play();
			}
			/*记录本次操作*/
			recorder.save_operation(judge,level);
			mymap.left_icon--;//图标对数减一
			update_the_map();//更新地图(new_map置零,图标隐藏)
			/*将posA，posB置零进行下一次判断*/
			posA = press_pos(0, 0);
			posB = press_pos(0, 0);
			if (mymap.left_icon == 0)
			{
				timer->stop();
				/*放个音效*/
				player2->setMedia(QUrl::fromLocalFile("music/level" + QString::number(level) + ".mp3"));
				player2->play();
				QMessageBox::StandardButton rb = QMessageBox::question(NULL, "You win!", "Go to the next level?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
				if (rb == QMessageBox::Yes)
				{
					go_to_next_level();
				}
				else this->close();

			}
		}
		else
		{
			/*将posB赋给posA，posB置零进行下一次判断*/
			posA = posB;
			posB = press_pos(0, 0);
			/*放个音效*/
			player3->setMedia(QUrl::fromLocalFile("music/wrong.mp3"));
			player3->play();
		}
	}
}

