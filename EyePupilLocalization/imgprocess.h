#ifndef IMGPROCESS_H  
#define IMGPROCESS_H  
#include <opencv2/opencv.hpp>   
#include <stdio.h>  
#include <vector>
#include <opencv2/core/core.hpp> 

typedef struct Box
{
	double x;
	double y;
	double r;
}Box;

//视频处理类  
class ImgProcess
{
private:
	double EyeRatio;
	cv::Mat inimg;//输入图像  
	cv::Mat outimg;//输出结果  
	cv::Mat Leye;//左眼
	cv::Mat Reye;//右眼
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

	void DivideEye(const cv::Mat divideimg);//分左右眼  
	cv::Mat GrayDetect(cv::Mat grayimg);//灰度处理
	cv::Mat Binary(const cv::Mat binaryimg, int value);//二值化处理
	void EdgeDetect(cv::Mat &edgeimg);//边缘检测  
	std::vector<cv::Vec3f> Hough(const cv::Mat midImage, int minradius, int maxradius);//hough变换   
	cv::Mat PlotC(std::vector<cv::Vec3f> circles, cv::Mat &midImage);//画出检测圆
	void RemoveSmallRegion(cv::Mat& Src, cv::Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode);//去除小面积
	Box circleLeastFit(const std::vector<cv::Point> points);//拟合圆检测
public:
	std::vector<cv::Vec3f> circles;//整体检测的瞳孔圆

	ImgProcess(cv::Mat image, double ratio = 1.3) :inimg(image), EyeRatio(ratio) {}//构造函数
	void Process();
	cv::Mat Outputimg();//输出结果  
	cv::Mat OutLeye();//输出左眼  
	cv::Mat OutReye();//输出右眼
};


#endif // IMGPROCESS_H  