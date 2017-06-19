#ifndef EYEPUPILLOCALIZATION_H
#define EYEPUPILLOCALIZATION_H

#include <QtWidgets/QMainWindow>
#include "ui_eyepupillocalization.h"
#include <qfiledialog.h>
#include "Mat2QImage.h"
#include "imgprocess.h" 
#include "MatMerge.h"

class EyePupilLocalization : public QMainWindow
{
	Q_OBJECT

public:
	EyePupilLocalization(QWidget *parent = 0);
	~EyePupilLocalization();

public slots:
	void on_pushButton_openvideo_clicked();//打开本地视频
	void on_pushButton_opencamera_clicked();//打开摄像头
	void on_pushButton_print_clicked();//打印
	void printPreviewSlot(QPrinter *printerPixmap);//打印预览
private:
	Ui::EyePupilLocalizationClass ui;
	//std::string videoStreamAddress = "http://192.168.1.233:8080/?action=stream?dummy=param.mjpg";//红外摄像头网络地址,改为了读取配置文件
	std::string videoStreamAddressLeft;
	std::string videoStreamAddressRight;
	QString fileName;//打开本地视频绝对地址
	cv::Mat Leye;//左眼Mat类型
	cv::Mat Reye;//右眼Mat类型
	QImage Limg;//左眼Image类型
	QImage Rimg;//右眼Image类型

	//保存上次信息
	int OldFrameNum = 0;//本次波形帧数
	QVector<double> OldFrameL;//本次左眼波形横坐标
	QVector<double> OldFrameR;//本次右眼波形横坐标
	QVector<double> OldReyeX;//本次右眼波形X坐标
	QVector<double> OldReyeY;//本次右眼波形Y坐标
	QVector<double> OldLeyeX;//本次左眼波形X坐标
	QVector<double> OldLeyeY;//本次左眼波形Y坐标
	QDateTime TESTtime;//测试时间
	QString str_TESTtime;//测试时间字符串标准格式

	cv::Mat NoVedio;

	void plotWight(bool IsLevel);//绘制波形
};

#endif 
