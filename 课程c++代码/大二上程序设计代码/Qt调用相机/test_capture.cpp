#include "test_capture.h"
Dialog::Dialog(QWidget *parent) 
{
	this->resize(600, 400);

	camera = new QCamera();
	//view_finder = new QCameraViewfinder();
	camera_image_capture = new QCameraImageCapture(camera);
	capture_button = new QPushButton();
	save_button = new QPushButton();
	exit_button = new QPushButton();
	display_label = new QLabel();

	QHBoxLayout *main_layout = new QHBoxLayout();
	QVBoxLayout *v_layout = new QVBoxLayout();

	display_label->setFixedSize(150, 150);
	display_label->setScaledContents(true);

	v_layout->addWidget(display_label);
	v_layout->addStretch();
	v_layout->addWidget(capture_button);
	v_layout->addWidget(save_button);
	v_layout->addWidget(exit_button);

	//main_layout->addWidget(view_finder);
	main_layout->addLayout(v_layout);

	connect(capture_button, &QPushButton::clicked, this, &Dialog::captureImage);
	connect(save_button, &QPushButton::clicked, this, &Dialog::saveImage);
	connect(exit_button, &QPushButton::clicked, this, &Dialog::close);
	connect(camera_image_capture, &QCameraImageCapture::imageCaptured, this, &Dialog::displayImage);

	camera_image_capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
	camera->setCaptureMode(QCamera::CaptureStillImage);
	//camera->setViewfinder(view_finder);
	camera->start(); //Æô¶¯ÉãÏñÍ·

	this->setLayout(main_layout);
	this->translateLanguage();
}

Dialog::~Dialog()
{

}

void Dialog::translateLanguage()
{
	this->setWindowTitle("testCapture");
	capture_button->setText(tr("capture"));
	save_button->setText(tr("save"));
	exit_button->setText(tr("exit"));
}

void Dialog::displayImage(int id, QImage image)
{
	display_label->setPixmap(QPixmap::fromImage(image));
}

void Dialog::captureImage()
{
	//½ØÍ¼
	camera_image_capture->capture();
}

void Dialog::saveImage()
{
	const QPixmap *pixmap = display_label->pixmap();
	if (pixmap)
	{
		pixmap->save("F:\\a.jpg");
	}
}