#include <MatMerge.h>

cv::Mat MatMerge(cv::Mat& img_left, cv::Mat& img_right)
{
	cv::Mat img_merge;
	cv::Mat outImg_left, outImg_right;

	cv::Size size(img_left.cols + img_right.cols + 1, MAX(img_left.rows, img_right.rows));
	
	img_merge.create(size, CV_MAKETYPE(img_left.depth(), 3));
	
	img_merge = cv::Scalar::all(0);
	outImg_left = img_merge(cv::Rect(0, 0, img_left.cols, img_left.rows));
	outImg_right = img_merge(cv::Rect(img_left.cols, 0, img_right.cols, img_right.rows));

	if (img_left.type() == CV_8U)
	{
		cvtColor(img_left, outImg_left, CV_GRAY2BGR);
	}
	else
	{
		img_left.copyTo(outImg_left);
	}

	if (img_right.type() == CV_8U)
	{
		cvtColor(img_right, outImg_right, CV_GRAY2BGR);
	}
	else
	{
		img_right.copyTo(outImg_right);
	}
	
	return img_merge;
}