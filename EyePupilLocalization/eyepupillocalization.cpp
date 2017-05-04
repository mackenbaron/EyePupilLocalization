#include "eyepupillocalization.h"

EyePupilLocalization::EyePupilLocalization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//初始化曲线
	ui.customPlot_x->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
		QCP::iSelectLegend | QCP::iSelectPlottables);//创建曲线范围
	ui.customPlot_x->xAxis->setLabel("TIME");//设置横坐标
	ui.customPlot_x->yAxis->setLabel("LEVEL");//设置纵坐标
	ui.customPlot_x->yAxis->setRange(-50, 50);//设置纵坐标范围
	ui.customPlot_x->addGraph();//增加第一条曲线
	ui.customPlot_x->graph(0)->setPen(QPen(Qt::red));//设置为红色
	ui.customPlot_x->addGraph();//在增加一条曲线
	ui.customPlot_x->graph(1)->setPen(QPen(Qt::blue));//设置为蓝色

	ui.customPlot_y->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
		QCP::iSelectLegend | QCP::iSelectPlottables);
	ui.customPlot_y->xAxis->setLabel("TIME");
	ui.customPlot_y->yAxis->setLabel("VERTICAL");
	ui.customPlot_y->yAxis->setRange(-50, 50);//设置纵坐标
	ui.customPlot_y->addGraph();
	ui.customPlot_y->graph(0)->setPen(QPen(Qt::red));
	ui.customPlot_y->addGraph();
	ui.customPlot_y->graph(1)->setPen(QPen(Qt::blue));

	label_name = new QLabel;
	label_name->setText("    DESIGNED BY HJY     ");
	ui.statusBar->addWidget(label_name);
	label_time = new QLabel;
	label_time->setText("     May , 2017  ");
	ui.statusBar->addWidget(label_time);
}

EyePupilLocalization::~EyePupilLocalization()
{
}

//打开视频
void EyePupilLocalization::on_pushButton_openvideo_clicked()
{
	fileName = QFileDialog::getOpenFileName(
		this,
		"Open Video",
		QDir::currentPath(),
		"Video files(*.avi)"
	);
	cv::VideoCapture capture(fileName.toStdString());
	if (!capture.isOpened())
	{
		//qDebug() << "未打开视频" ;
		QMessageBox::information(this, "Warn", "No video selected");
		return;
	}
	//double rate = capture.get(CV_CAP_PROP_FPS);
	double numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
	
	QVector<double> Time, Rx, Ry, Lx, Ly;

	bool stop(false);
	cv::Mat frame;
	cv::Mat EyeShow = cv::imread("C:\\Users\\LZH\\Documents\\Visual Studio 2015\\Projects\\EyePupilLocalization\\EyePupilLocalization\\Resources\\eye.png", -1);
	cv::resize(EyeShow, EyeShow, cv::Size(120, 60), 0, 0);//设置大小
	cv::namedWindow("Project");
	cv::imshow("Project", EyeShow);
	//cv::destroyAllWindows();
	ui.customPlot_x->xAxis->setRange(0, numFrames);//设置横坐标
	ui.customPlot_y->xAxis->setRange(0, numFrames);//设置横坐标

	bool IsReyeCenter(false);//是否右眼出来第一个定位坐标
	bool IsLeyeCenter(false);//是否左眼出来第一个定位坐标
	int FrameNum = 0;//视频处理帧的次数
	CvPoint ReyeCenter;//右眼中心
	CvPoint LeyeCenter;//左眼中心

	//cv::Mat Eyetest = cv::imread("C:\\Users\\LZH\\Pictures\\testeye\\1.png", -1);

	while (!stop)
	{
		if (!capture.read(frame))
		{
			break;
		}
		++FrameNum;
		ImgProcess pro(frame,1.5);
		pro.Process();

		Leye = pro.OutLeye();
		Reye = pro.OutReye();

		Limg = Mat2QImage(Leye);
		Rimg = Mat2QImage(Reye);
		ui.label_Leye->setPixmap(QPixmap::fromImage(Limg));//显示出来
		ui.label_Reye->setPixmap(QPixmap::fromImage(Rimg));

		//插入坐标
		for (cv::Vec3f box : pro.circles)
		{
			if (box[0] < frame.cols / 2)//X坐标小于一半位置为左眼
			{
				//左眼
				ui.lcdNumber_Lx->display(floor(box[0]));
				ui.lcdNumber_Ly->display(floor(box[1]));
				ui.lcdNumber_Lr->display(floor(box[2]));
				if (!IsLeyeCenter)
				{
					LeyeCenter.x = box[0];
					LeyeCenter.y = box[1];
					IsLeyeCenter = true;
					Lx.push_back(0);
					Ly.push_back(0);
					Time.push_back(FrameNum);
					ui.customPlot_x->graph(0)->setData(Time, Lx);
					ui.customPlot_y->graph(0)->setData(Time, Ly);
				}
				else
				{
					ui.customPlot_x->graph(0)->addData(FrameNum, box[0] - LeyeCenter.x);
					ui.customPlot_y->graph(0)->addData(FrameNum, box[1] - LeyeCenter.y);
				}	
			}
			else
			{
				//右眼
				ui.lcdNumber_Rx->display(floor(box[0]));
				ui.lcdNumber_Ry->display(floor(box[1]));
				ui.lcdNumber_Rr->display(floor(box[2]));
				if (!IsReyeCenter)
				{
					ReyeCenter.x = box[0];
					ReyeCenter.y = box[1];
					IsReyeCenter = true;
					Rx.push_back(0);
					Ry.push_back(0);
					Time.push_back(FrameNum);
					ui.customPlot_x->graph(1)->setData(Time, Rx);
					ui.customPlot_y->graph(1)->setData(Time, Ry);
				}
				else
				{
					ui.customPlot_x->graph(1)->addData(FrameNum, box[0] - ReyeCenter.x);
					ui.customPlot_y->graph(1)->addData(FrameNum, box[1] - ReyeCenter.y);
				}
			}
		}
		ui.customPlot_x->replot();
		ui.customPlot_y->replot();
		cv::waitKey(1);
	}
}