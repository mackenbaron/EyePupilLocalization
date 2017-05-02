#ifndef IMGPROCESS_H  
#define IMGPROCESS_H  
#include <opencv2/opencv.hpp>  
#include <iostream>  
#include <stdio.h>  
#include <vector>
#include <opencv2/core/core.hpp> 

//视频处理类  
class ImgProcess
{
private:
	double EyeRatio;
	cv::Mat inimg;//输入图像  
	cv::Mat outimg;//输出结果  
	cv::Mat Leye;//左眼
	cv::Mat Reye;//右眼
	std::vector<cv::Vec3f> Lcircles;//左眼霍夫圆
	std::vector<cv::Vec3f> Rcircles;//右眼霍夫圆
	std::vector<std::vector<cv::Point>> Lcontours;//左眼轮廓检测
	std::vector<std::vector<cv::Point>> Rcontours;//右眼轮廓检测
	std::vector<cv::Vec4i> Lhierarchy;//左眼轮廓关系
	std::vector<cv::Vec4i> Rhierarchy;//右眼轮廓关系
	double Lmaxarea = 0;//左眼最大轮廓
	int LmaxAreaIndex = 0;//左眼最大轮廓下标
	double Rmaxarea = 0;//右眼最大轮廓
	int RmaxAreaIndex = 0;//右眼最大轮廓下标
	cv::Rect Rrect;//左眼轮廓边界
	cv::Rect Lrect;//右眼轮廓边界
	//static RadiusRange Radiusrange;//眼睛半径范围 

	void DivideEye(const cv::Mat divideimg);//分左右眼  
	cv::Mat GrayDetect(cv::Mat grayimg);//灰度处理
	cv::Mat Binary(const cv::Mat binaryimg, int value);//二值化处理
	void EdgeDetect(cv::Mat &edgeimg);//边缘检测  
	std::vector<cv::Vec3f> Hough(const cv::Mat midImage, int minradius, int maxradius);//hough变换   
	cv::Mat PlotC(std::vector<cv::Vec3f> circles, cv::Mat &midImage);//画HOUGH变换的检测结果  
	void RemoveSmallRegion(cv::Mat& Src, cv::Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode);//去除小面积

public:
	std::vector<cv::Vec3f> circles;//整体霍夫圆
	//ImgProcess(cv::Mat image) :inimg(image) {}
	ImgProcess(cv::Mat image, double ratio = 1.3) :inimg(image), EyeRatio(ratio) {}
	//void Process(int & LminRadius, int & LmaxRadius, int & RminRadius, int & RmaxRadius);//检测过程
	void Process(int* transmit);
	cv::Mat Outputimg();//输出结果  
	cv::Mat OutLeye();//输出左眼  
	cv::Mat OutReye();//输出右眼
};


#endif // IMGPROCESS_H  