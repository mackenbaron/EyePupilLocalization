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

private:
	Ui::EyePupilLocalizationClass ui;
	QString fileName;
	cv::Mat Leye;//×óÑÛ
	cv::Mat Reye;//ÓÒÑÛ
	QImage Limg;
	QImage Rimg;
	QLabel *label_name;
	QLabel *label_time;
};

#endif // EYEPUPILLOCALIZATION_H
