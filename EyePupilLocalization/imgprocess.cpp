#include "imgprocess.h"  

//RadiusRange ImgProcess::Radiusrange = { 5,30,5,30 };

//输出结果
cv::Mat ImgProcess::Outputimg()
{
	return outimg;
}

//分左右眼
void ImgProcess::DivideEye(const cv::Mat divideimg)
{
	if (divideimg.cols > 0 && divideimg.rows > 0)//cols是列数320，rows是行数120
	{
		CvRect leye_box;
		leye_box.x = 1;
		leye_box.y = 1;
		leye_box.height = divideimg.rows - 1;
		leye_box.width = divideimg.cols / 2 - 1;
		CvRect reye_box;
		reye_box.x = leye_box.x + leye_box.width;
		reye_box.y = 1;
		reye_box.height = divideimg.rows - 1;
		reye_box.width = divideimg.cols / 2 - 1;
		Leye = divideimg(leye_box);
		Reye = divideimg(reye_box);
	}

}

//输出左眼
cv::Mat ImgProcess::OutLeye()//输出左眼
{
	return Leye;
}

//输出右眼
cv::Mat ImgProcess::OutReye()//输出右眼
{
	return Reye;
}

//瞳孔定位处理
void ImgProcess::Process(int* transmit)
{
	cv::Mat grayimg;
	double temparea;
	grayimg = GrayDetect(inimg);//得到灰度图,此时inimg没有被修改
	EdgeDetect(grayimg);//边缘检测
	DivideEye(grayimg);//左右眼分割
	cv::findContours(Leye, Lcontours, Lhierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);//寻找左眼轮廓
	cv::findContours(Reye, Rcontours, Rhierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);//寻找右眼轮廓
	if (Lcontours.size() > 0)//左眼有轮廓
	{
		for (int i = 0; i < Lcontours.size(); ++i)
		{
			temparea = fabs(cv::contourArea(Lcontours[i]));
			if (temparea > Lmaxarea)
			{
				Lmaxarea = temparea;//左眼最大轮廓面积
				LmaxAreaIndex = i;//左眼最大轮廓下标
				continue;
			}
		}
		//闭眼检测
		Lrect = cv::boundingRect(Lcontours[LmaxAreaIndex]);
		if ((Lrect.width / (float)Lrect.height) < EyeRatio && (Lrect.height / (float)Lrect.width) < EyeRatio && Lrect.width > 15 && Lrect.height > 15)//左眼闭眼检测
		{
			Lcircles = Hough(Leye, transmit[0], transmit[1]);
		}
	}
	if (Rcontours.size() > 0)//右眼有轮廓
	{
		for (int i = 0; i < Rcontours.size(); ++i)
		{
			temparea = fabs(cv::contourArea(Rcontours[i]));
			if (temparea > Rmaxarea)
			{
				Rmaxarea = temparea;
				RmaxAreaIndex = i;
				continue;
			}
		}
		//闭眼检测
		Rrect = cv::boundingRect(Rcontours[RmaxAreaIndex]);
		if ((Rrect.width / (float)Rrect.height) < EyeRatio && (Rrect.height / (float)Rrect.width) < EyeRatio && Rrect.width > 15 && Rrect.height > 15)//右眼闭眼检测
		{
			Rcircles = Hough(Reye, transmit[2], transmit[3]);
		}
	}
	
	int MaxRadius = 0;//最大半径
	size_t MaxNum = 0;
	if (Lcircles.size() > 0)
	{
		for (size_t i = 0; i < Lcircles.size(); ++i)
		{
			if (cvRound(Lcircles[i][2]) >= MaxRadius)
			{
				MaxNum = i;
			}
		}
		if (transmit[4] == 0 && transmit[5] == 0 && Lcircles[MaxNum][0] > 5)
		{
			//第一次情况
			transmit[4] = Lcircles[MaxNum][0];//圆心x坐标
			transmit[5] = Lcircles[MaxNum][1];//圆心y坐标
		}
		else
		{
			if (abs(transmit[4] - Lcircles[MaxNum][0]) < 30 && abs(transmit[5] - Lcircles[MaxNum][1]) < 30)
			{
				//圆心半径二次检验
				circles.push_back(Lcircles[MaxNum]);//左眼最大霍夫圆
				transmit[0] = Lcircles[MaxNum][2] - 8;
				transmit[1] = Lcircles[MaxNum][2] + 8;
			}
		}
	}
	if (Rcircles.size() > 0)
	{
		MaxRadius = 0;//重新初始化
		MaxNum = 0;
		for (size_t i = 0; i < Rcircles.size(); ++i)
		{
			Rcircles[i][0] += inimg.cols / 2 - 1;
			if (cvRound(Rcircles[i][2]) >= MaxRadius)
			{
				MaxNum = i;
			}
		}
		if (transmit[6] == 0 && transmit[7] == 0 && Rcircles[MaxNum][0] > 5)
		{
			//第一次情况
			transmit[6] = Rcircles[MaxNum][0];//圆心x坐标
			transmit[7] = Rcircles[MaxNum][1];//圆心y坐标
		}
		else
		{
			if (abs(transmit[6] - Rcircles[MaxNum][0]) < 30 && abs(transmit[7] - Rcircles[MaxNum][1]) < 30)
			{
				//圆心半径二次检验
				circles.push_back(Rcircles[MaxNum]);//右眼最大霍夫圆
				transmit[2] = Rcircles[MaxNum][2] - 8;
				transmit[3] = Rcircles[MaxNum][2] + 8;
			}
		}
	}
	if (circles.size() > 0)
	{
		outimg = PlotC(circles, inimg);
	}
	else
	{
		//没有霍夫圆
		outimg = inimg;
	}
	DivideEye(outimg);//左右眼再次分割,此时已经有了霍夫圆
	if (Lcontours.size() > 0)
	{
		cv::drawContours(Leye, Lcontours, LmaxAreaIndex, cv::Scalar(0, 0, 255), 1);//左眼轮廓显示
	}
	if (Rcontours.size() > 0)
	{
		cv::drawContours(Reye, Rcontours, RmaxAreaIndex, cv::Scalar(0, 0, 255), 1);//右眼轮廓显示
	}
}

//灰度处理
cv::Mat ImgProcess::GrayDetect(cv::Mat grayimg)
{
	cv::Mat grayout;
	cvtColor(grayimg, grayimg, CV_BGR2GRAY);//灰度化处理
	medianBlur(grayimg, grayimg, 9);//中值滤波
	grayout = Binary(grayimg, 43);//二值化处理
	//RemoveSmallRegion(grayout, grayout, 50, 0, 0);//可以不去除小面积
	RemoveSmallRegion(grayout, grayout, 250, 1, 0);//去除白区域
	return grayout;
}

//二值化处理
cv::Mat ImgProcess::Binary(const cv::Mat binaryimg, int value)
{
	cv::Mat binaryout = binaryimg < value;
	return binaryout;
}

//边缘检测
void ImgProcess::EdgeDetect(cv::Mat &edgeimg)
{
	//Mat edgeout;
	Canny(edgeimg, edgeimg, 100, 250, 3);//输入图像,输出图像,低阈值,高阈值，opencv建议是低阈值的3倍,内部sobel滤波器大小  
										 //return edgeimg;
}

//hough检测
std::vector<cv::Vec3f> ImgProcess::Hough(const cv::Mat midImage, int minradius, int maxradius)
{
	std::vector<cv::Vec3f> circles;
	HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 3, 5, 100, 30, minradius, maxradius);
	return circles;
}

//画HOUGH变换的检测结果  
cv::Mat ImgProcess::PlotC(std::vector<cv::Vec3f> circles, cv::Mat &midImage)
{
	for (size_t i = 0; i < circles.size(); i++)
	{
		//对圆心位置和半径进行四舍五入
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(midImage, center, 1, cv::Scalar(0, 0, 255), -1, 8);
		//绘制圆轮廓  
		circle(midImage, center, radius, cv::Scalar(255, 0, 0), 1, 8);
	}
	return midImage;
}

//CheckMode: 0代表去除黑区域，1代表去除白区域; NeihborMode：0代表4邻域，1代表8邻域;  
void ImgProcess::RemoveSmallRegion(cv::Mat& Src, cv::Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode)
{
	int RemoveCount = 0;       //记录除去的个数  
							   //记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查  
	cv::Mat Pointlabel = cv::Mat::zeros(Src.size(), CV_8UC1);

	if (CheckMode == 1)
	{
		std::cout << "Mode: 去除小区域. ";
		for (int i = 0; i < Src.rows; ++i)
		{
			uchar* iData = Src.ptr<uchar>(i);
			uchar* iLabel = Pointlabel.ptr<uchar>(i);
			for (int j = 0; j < Src.cols; ++j)
			{
				if (iData[j] < 10)
				{
					iLabel[j] = 3;
				}
			}
		}
	}
	else
	{
		std::cout << "Mode: 去除孔洞. ";
		for (int i = 0; i < Src.rows; ++i)
		{
			uchar* iData = Src.ptr<uchar>(i);
			uchar* iLabel = Pointlabel.ptr<uchar>(i);
			for (int j = 0; j < Src.cols; ++j)
			{
				if (iData[j] > 10)
				{
					iLabel[j] = 3;
				}
			}
		}
	}

	std::vector<cv::Point2i> NeihborPos;  //记录邻域点位置  
	NeihborPos.push_back(cv::Point2i(-1, 0));
	NeihborPos.push_back(cv::Point2i(1, 0));
	NeihborPos.push_back(cv::Point2i(0, -1));
	NeihborPos.push_back(cv::Point2i(0, 1));
	if (NeihborMode == 1)
	{
		std::cout << "Neighbor mode: 8邻域." << std::endl;
		NeihborPos.push_back(cv::Point2i(-1, -1));
		NeihborPos.push_back(cv::Point2i(-1, 1));
		NeihborPos.push_back(cv::Point2i(1, -1));
		NeihborPos.push_back(cv::Point2i(1, 1));
	}
	else std::cout << "Neighbor mode: 4邻域." << std::endl;
	int NeihborCount = 4 + 4 * NeihborMode;
	int CurrX = 0, CurrY = 0;
	//开始检测  
	for (int i = 0; i < Src.rows; ++i)
	{
		uchar* iLabel = Pointlabel.ptr<uchar>(i);
		for (int j = 0; j < Src.cols; ++j)
		{
			if (iLabel[j] == 0)
			{
				//********开始该点处的检查**********  
				std::vector<cv::Point2i> GrowBuffer;                                      //堆栈，用于存储生长点  
				GrowBuffer.push_back(cv::Point2i(j, i));
				Pointlabel.at<uchar>(i, j) = 1;
				int CheckResult = 0;                                               //用于判断结果（是否超出大小），0为未超出，1为超出  

				for (int z = 0; z<GrowBuffer.size(); z++)
				{

					for (int q = 0; q<NeihborCount; q++)                                      //检查四个邻域点  
					{
						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界  
						{
							if (Pointlabel.at<uchar>(CurrY, CurrX) == 0)
							{
								GrowBuffer.push_back(cv::Point2i(CurrX, CurrY));  //邻域点加入buffer  
								Pointlabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查  
							}
						}
					}

				}
				if (GrowBuffer.size()>AreaLimit) CheckResult = 2;                 //判断结果（是否超出限定的大小），1为未超出，2为超出  
				else { CheckResult = 1;   RemoveCount++; }
				for (int z = 0; z<GrowBuffer.size(); z++)                         //更新Label记录  
				{
					CurrX = GrowBuffer.at(z).x;
					CurrY = GrowBuffer.at(z).y;
					Pointlabel.at<uchar>(CurrY, CurrX) += CheckResult;
				}
				//********结束该点处的检查**********  


			}
		}
	}

	CheckMode = 255 * (1 - CheckMode);
	//开始反转面积过小的区域  
	for (int i = 0; i < Src.rows; ++i)
	{
		uchar* iData = Src.ptr<uchar>(i);
		uchar* iDstData = Dst.ptr<uchar>(i);
		uchar* iLabel = Pointlabel.ptr<uchar>(i);
		for (int j = 0; j < Src.cols; ++j)
		{
			if (iLabel[j] == 2)
			{
				iDstData[j] = CheckMode;
			}
			else if (iLabel[j] == 3)
			{
				iDstData[j] = iData[j];
			}
		}
	}

	std::cout << RemoveCount << " objects removed." << std::endl;
}