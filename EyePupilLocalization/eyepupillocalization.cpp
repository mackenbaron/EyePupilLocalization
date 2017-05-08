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

	ui.customPlot_print->hide();
	ui.customPlot_print->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
		QCP::iSelectLegend | QCP::iSelectPlottables);//创建曲线范围
	ui.customPlot_print->xAxis->setLabel("TIME");//设置横坐标
	ui.customPlot_print->yAxis->setRange(-50, 50);//设置纵坐标范围
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
		QMessageBox::warning(this, "Warn", "No video selected");
		return;
	}
	double numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
	QVector<double> TimeR, TimeL, Rx, Ry, Lx, Ly;
	OldFrameNum = numFrames;
	OldFrameR.clear();
	OldFrameL.clear();
	OldReyeX.clear();
	OldReyeY.clear();
	OldLeyeX.clear();
	OldLeyeY.clear();
	bool stop(false);
	cv::Mat frame;
	cv::namedWindow("Video");//新建原始视频窗口
	ui.customPlot_x->xAxis->setRange(0, numFrames);//设置横坐标
	ui.customPlot_y->xAxis->setRange(0, numFrames);//设置横坐标

	bool IsReyeCenter(false);//是否右眼出来第一个定位坐标
	bool IsLeyeCenter(false);//是否左眼出来第一个定位坐标
	int FrameNum = 0;//视频处理帧的次数
	CvPoint ReyeCenter;//右眼中心
	CvPoint LeyeCenter;//左眼中心
	while (!stop)
	{
		if (!capture.read(frame))//读取视频每帧
		{
			break;//当没有帧数读取时就退出循环
		}
		cv::imshow("Video", frame);//显示原始视频
		++FrameNum;
		ImgProcess pro(frame,1.7);//进行类操作
		pro.Process();

		Leye = pro.OutLeye();//输出左眼
		Reye = pro.OutReye();//输出右眼

		Limg = Mat2QImage(Leye);//将左眼MAT类型装为IMAGE类型
		Rimg = Mat2QImage(Reye);//将右眼MAT类型装为IMAGE类型
		ui.label_Leye->setPixmap(QPixmap::fromImage(Limg));//在程序界面将左眼眼显示出来
		ui.label_Reye->setPixmap(QPixmap::fromImage(Rimg));//在程序界面将右眼显示出来

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
					TimeL.push_back(FrameNum);
					ui.customPlot_x->graph(0)->setData(TimeL, Lx);
					ui.customPlot_y->graph(0)->setData(TimeL, Ly);
					OldLeyeX.push_back(0);
					OldLeyeY.push_back(0);
				}
				else
				{
					ui.customPlot_x->graph(0)->addData(FrameNum, box[0] - LeyeCenter.x);
					ui.customPlot_y->graph(0)->addData(FrameNum, box[1] - LeyeCenter.y);
					OldLeyeX.push_back(box[0] - LeyeCenter.x);
					OldLeyeY.push_back(box[1] - LeyeCenter.y);
				}
				OldFrameL.push_back(FrameNum);
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
					TimeR.push_back(FrameNum);
					ui.customPlot_x->graph(1)->setData(TimeR, Rx);
					ui.customPlot_y->graph(1)->setData(TimeR, Ry);
					OldReyeX.push_back(0);
					OldReyeY.push_back(0);
				}
				else
				{
					ui.customPlot_x->graph(1)->addData(FrameNum, box[0] - ReyeCenter.x);
					ui.customPlot_y->graph(1)->addData(FrameNum, box[1] - ReyeCenter.y);
					OldReyeX.push_back(box[0] - ReyeCenter.x);
					OldReyeY.push_back(box[1] - ReyeCenter.y);
				}
				OldFrameR.push_back(FrameNum);
			}
		}
		ui.customPlot_x->replot();//重绘x坐标波形图
		ui.customPlot_y->replot();//重绘y坐标波形图
		cv::waitKey(1);
	}
	cv::destroyWindow("Video");//销毁窗口
}
//打开摄像头
void EyePupilLocalization::on_pushButton_opencamera_clicked()
{
	cv::VideoCapture vcap;//定义摄像头打开对象
	QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Choose", "Do you want to open PC camera?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);//提示选择打开哪一个摄像头
	if (rb == QMessageBox::Yes)//打开本机PC上的摄像头
	{
		if (!vcap.open(0))
		{
			QMessageBox::warning(this, "Warn", "No Camera");
			return;
		}
	}
	else if (rb == QMessageBox::No)//打开网络摄像头
	{
		if (!vcap.open(videoStreamAddress))
		{
			QMessageBox::warning(this, "Warn", "No Camera");
			return;
		}
	}
	else//取消打开
	{
		return;
	}
	cv::namedWindow("Camera Video");
	bool stop(false);
	cv::Mat frame;
	while (!stop)
	{
		if (!vcap.read(frame))
		{
			break;
		}
		cv::imshow("Camera Video", frame);//显示摄像头内容
		if (cv::waitKey(5) == 27)//ESC的ASCII码为27
		{
			break;//按下ESC退出
		}
	}
	cv::destroyWindow("Camera Video");//销毁窗口
}
//打印
void EyePupilLocalization::on_pushButton_print_clicked()
{
	if (OldFrameNum == 0)
	{
		QMessageBox::warning(this, "Warn", "No Waveforms");
		return;
	}
	QPrinter printer;//新建打印机对象
	printer.setPageSize(QPrinter::A4);//设置打印为A4纸张

	QPainter painter(&printer);//在打印纸张上绘图
	QRect rect = painter.viewport();
	QRect rectText1(0, 0, 700, 50);
	QRect rectText2(0, 450, 700, 50);
	painter.drawText(rectText1, Qt::AlignCenter, tr("LEVEL"));
	painter.drawText(rectText2, Qt::AlignCenter, tr("VERTICAL"));
	QSize size = ui.customPlot_print->size();//获取plotwight控件的大小
	painter.setViewport(rect.x(), rect.y() + 50, size.width(), size.height());//设置水平波形图轨迹方位
	plotWight(true);//绘制水平波形图
	ui.customPlot_print->render(&painter);//将水平波形图转到painter中去
	painter.setViewport(rect.x(), rect.y() + size.height(), size.width(), rect.y() + size.height());//设置竖直波形图轨迹方位
	plotWight(false);//绘制竖直波形图
	ui.customPlot_print->render(&painter);//将竖直波形图转到painter中去
	painter.end();

	/*****打印预览，未完待续*****/
	//QPrintPreviewDialog preview(&printer, this);//打印预览
	//QPrintDialog printdlg(&printer, this);//打印预览
	//preview.showNormal();
	//preview.setWindowTitle(tr("Print Waveform"));
	//connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printView(QPrinter*)));
	//preview.exec();
	/**********/
}
//绘制波形
void EyePupilLocalization::plotWight(bool IsLevel)
{
	ui.customPlot_print->addGraph();//增加第一条曲线
	ui.customPlot_print->xAxis->setRange(0, OldFrameNum);//设置横坐标
	ui.customPlot_print->graph(0)->setPen(QPen(Qt::red));//设置为红色
	ui.customPlot_print->addGraph();//在增加一条曲线
	ui.customPlot_print->graph(1)->setPen(QPen(Qt::blue));//设置为蓝色
	if (IsLevel)
	{
		//水平位置
		ui.customPlot_print->yAxis->setLabel("LEVEL");
		ui.customPlot_print->graph(0)->setData(OldFrameL, OldLeyeX);
		ui.customPlot_print->graph(1)->setData(OldFrameR, OldReyeX);
	}
	else
	{
		//竖直位置
		ui.customPlot_print->yAxis->setLabel("VERTICAL");
		ui.customPlot_print->graph(0)->setData(OldFrameL, OldLeyeY);
		ui.customPlot_print->graph(1)->setData(OldFrameR, OldReyeY);
	}
	ui.customPlot_print->replot();
}