#ifndef EYEPUPILLOCALIZATION_H
#define EYEPUPILLOCALIZATION_H

#include <QtWidgets/QMainWindow>
#include "ui_eyepupillocalization.h"
#include <qfiledialog.h>
#include "Mat2QImage.h"
#include "imgprocess.h" 

class EyePupilLocalization : public QMainWindow
{
	Q_OBJECT

public:
	EyePupilLocalization(QWidget *parent = 0);
	~EyePupilLocalization();

public slots:
	void on_pushButton_openvideo_clicked();
	void on_pushButton_print_clicked();
	void on_pushButton_opencamera_clicked();
private:
	Ui::EyePupilLocalizationClass ui;
	std::string videoStreamAddress = "http://192.168.1.233:8080/?action=stream?dummy=param.mjpg";
	QString fileName;
	cv::Mat Leye;//左眼
	cv::Mat Reye;//右眼
	QImage Limg;
	QImage Rimg;
	QLabel *label_name;
	QLabel *label_time;
	QPrinter printer;
	//QPrintPreviewDialog preview;

	//保存上次信息
	int OldFrameNum = 0;
	QVector<double> OldFrameL;
	QVector<double> OldFrameR;
	QVector<double> OldReyeX;
	QVector<double> OldReyeY;
	QVector<double> OldLeyeX;
	QVector<double> OldLeyeY;

	void plotWight(bool IsLevel);
};

#endif // EYEPUPILLOCALIZATION_H
