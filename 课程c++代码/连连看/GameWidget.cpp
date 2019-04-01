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
	BGM_Group->setExclusive(true);//���û���
	for (int i = 0; i < 3; ++i)
	{
		QRadioButton *pButton = new QRadioButton(this);

		// �����ı�
		pButton->setText(QString::fromLocal8Bit("bgm%1").arg(i + 1));
		pButton->setGeometry(10 + 50 * i, 8, 50, 20);
		BGM_Group->addButton(pButton);
	}
	//�����źŲ�
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
	if (!rep) timer->start();//������ǻط�ģʽ���ͼ�ʱ
	timer2 = new QTimer(this);
	timer2->setInterval(900);
	if (rep) timer2->start();//����ǻط�ģʽ���Ϳ�ʼ��ʱ

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

	/*��ʾ������,����һ���ؿ���*/
	properties = new QLabel(this);
	properties->setText("promp:" + QString::number(promp_num) +
						"   bomb:" + QString::number(bomb_num) +
						"                    level:" + QString::number(level) +
						"           scores:" + QString::number(scores));
	properties -> setGeometry(10, 30, 640, 20);
	/*����*/
	ft.setPointSize(12);
	properties->setFont(ft);
	
}


GameWidget::~GameWidget()
{

}

void GameWidget::paintEvent(QPaintEvent *)
{
	int this_five[5];//�����������
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
	if (temp == 0) return;//�߿��ް�ť
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
	button_arr[i][j]->show();//����֮����
	/*connect each element to the signalMapper, in order to send i and j.*/
	connect(button_arr[i][j], SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button_arr[i][j], i * 100 + j);
}

void GameWidget::update_the_map()
{
	/*����ը������ʾ*/
	property_manager();

	/*����box*/
	int num = mymap.new_map[posA.getx()][posA.gety()] - 1;
	std::vector<int>::iterator iter = std::find(mymap.box[num].begin(), mymap.box[num].end(), posA.getx() * 100 + posA.gety());
	if (iter != mymap.box[num].end()) mymap.box[num].erase(iter);
	/*��ɾһ����ɾ��һ���������³�����*/
	iter = std::find(mymap.box[num].begin(), mymap.box[num].end(), posB.getx() * 100 + posB.gety());
	if (iter != mymap.box[num].end()) mymap.box[num].erase(iter);
	
	/*��new_map������*/
	mymap.new_map[posA.getx()][posA.gety()] = 0;
	mymap.new_map[posB.getx()][posB.gety()] = 0;
	
	/*����*/
	repaint();
	//draw.draw_line(judge.current_salient[0], judge.current_salient,posA,posB,judge.is_swap);
	/*ͼ�λ��������ذ�ť*/
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
	/*��������ڻطţ��Ǿ�ÿһ�ض�¼������˳��Ѹ�level��operation.txt���һ��*/
	if (!rep)
	{
		recorder.save_now(mymap, temp_time, scores, level, promp_num, bomb_num, 1, level);
		recorder.clear_operation(level);
	}
}

void GameWidget::go_to_next_level()
{
	/*�ؿ���+1*/
	level += 1;
	/*����ʣ��ʱ�佱��ը������ʾ*/
	promp_num += temp_time / 20;
	bomb_num += temp_time / 30;
	property_manager();
	
	/*����ܳ���12*12�ĵ�ͼ*/
	if (Map::get_mapsize() < 12)
	{
		/*�����Ѷ�,���¿�ʼ*/
		Map::set_mapsize(Map::get_mapsize() + 2);
		temp_time = 100 - 3*level;//������Լ��ٻ�����һЩ
	}
	else temp_time = 100 - 3*level;
	last_actiontime = temp_time;
	/*��ʼ��ʱ*/
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
	/*ÿһ�ζ���operation(n).txt�����Ԫ��*/
	recorder.read_oper(rep);//ע�����n
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
		/*û��ʹ��ը��*/
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
	if (temp_time == 0||(last_actiontime-temp_time>20))//��ʱ����
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
	/*�Ȱ�posA��posB����*/
	posA = press_pos(0, 0);
	posB = press_pos(0, 0);
	/*��ai�ҵ�*/
	ai.ai_find(mymap, judge);
	/*���ҵ��ˣ�ģ����������*/
	if (ai.get_findit())
	{
		/*��ʾ����1*/
		promp_num--;
		/*ģ����*/
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
	d.setInputMode(QInputDialog::IntInput);  //TextInput�����ı���DoubleInput����double����
	if (d.exec() == QInputDialog::Accepted)
		n = d.intValue();           //TextValue��doubleValue
	/*ע�����һ������Ҫ��*/
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
		if (judge.get_isok()||use_bomb)//��ը������ͨ·
		{
			last_actiontime = temp_time;//��¼����ʱ�䣬���ڼ���Ƿ�ʱ
			scores += mymap.create_randnum(15, 3) * 3;//�ӷ֣���һ���������
			/*���ʹ����ը������ը������1*/
			if (use_bomb)
			{
				bomb_num--;
				player3->setMedia(QUrl::fromLocalFile("music/bomb.mp3"));
				player3->play();
			}
			else
			{
				/*�Ÿ���Ч*/
				player3->setMedia(QUrl::fromLocalFile("music/ding.mp3"));
				player3->play();
			}
			/*��¼���β���*/
			recorder.save_operation(judge,level);
			mymap.left_icon--;//ͼ�������һ
			update_the_map();//���µ�ͼ(new_map����,ͼ������)
			/*��posA��posB���������һ���ж�*/
			posA = press_pos(0, 0);
			posB = press_pos(0, 0);
			if (mymap.left_icon == 0)
			{
				timer->stop();
				/*�Ÿ���Ч*/
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
			/*��posB����posA��posB���������һ���ж�*/
			posA = posB;
			posB = press_pos(0, 0);
			/*�Ÿ���Ч*/
			player3->setMedia(QUrl::fromLocalFile("music/wrong.mp3"));
			player3->play();
		}
	}
}

