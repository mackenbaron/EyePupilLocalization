#ifndef EYEPUPILLOCALIZATION_H
#define EYEPUPILLOCALIZATION_H

#include <QtWidgets/QMainWindow>
#include "ui_eyepupillocalization.h"
#include <qfiledialog.h>
#include "Mat2QImage.h"
#include "imgprocess.h" 
#include "MatMerge.h"
#include <conio.h>

class EyePupilLocalization : public QMainWindow
{
	Q_OBJECT

public:
	EyePupilLocalization(QWidget *parent = 0);
	~EyePupilLocalization();

public slots:
	void on_pushButton_openvideo_clicked();//打开本地视频
	void on_pushButton_closecamera_clicked();//关闭摄像头
	void on_pushButton_opencamera_clicked();//打开摄像头
	void on_pushButton_print_clicked();//打印
	void printPreviewSlot(QPrinter *printerPixmap);//打印预览

private slots:
	void readFarme();

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
	cv::VideoCapture vcapLeft;//定义左摄像头打开对象
	cv::VideoCapture vcapRight;//定义右摄像头打开对象
	cv::VideoCapture capture;//定义本地视频打开对象
	cv::Mat frameL;//右眼
	cv::Mat frameR;//左眼
	cv::Mat frameAll;//本地视频帧,双眼
	int FrameNum;//帧数
	bool IsReyeCenter;//是否右眼出来第一个定位坐标
	bool IsLeyeCenter;//是否左眼出来第一个定位坐标
	CvPoint ReyeCenter;//右眼中心
	CvPoint LeyeCenter;//左眼中心
	QVector<double> TimeR, TimeL, Rx, Ry, Lx, Ly;//绘图点坐标
	QTimer *timer;//定时器
	int EyeNum;//眼睛数目

	QImage NoVideoImage;
	int LabelWidth;
	int LabelHeight;

	cv::Mat Pic_Leye;
	cv::Mat Pic_Reye;

	QImage PicImgLeye;
	QImage PicImgReye;
	double plx;
	double ply;
	double prx;
	double pry;
	cv::Point Lcenter;
	cv::Point Rcenter;

	void plotWight(bool IsLevel);//绘制波形
	
};

#endif 
