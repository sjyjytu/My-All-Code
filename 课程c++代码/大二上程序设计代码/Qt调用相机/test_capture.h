#ifndef TEST_CAPTURE_H
#define TEST_CAPTURE_H

#include <QWidget>
#include <qpushbutton.h>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QList>
#include <QDebug>
#include <QImage>
#include <qdialog.h>
#include <qlabel.h>
#include <qlayout.h>


class Dialog : public QWidget
{
	Q_OBJECT

public:
	explicit Dialog(QWidget *parent = 0);
	~Dialog();

	void translateLanguage();
	void displayImage(int id, QImage image);
	void captureImage();
	void saveImage();
private:
	QCamera * camera;
	//QCameraViewfinder *view_finder;
	QCameraImageCapture *camera_image_capture;
	QPushButton *capture_button;
	QPushButton *save_button;
	QPushButton *exit_button;
	QLabel *display_label;

};

#endif // TEST_CAPTURE_H