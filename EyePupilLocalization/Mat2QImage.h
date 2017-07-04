#ifndef MAT2QIMAGE_H  
#define MAT2QIMAGE_H  

#include <QtGui>  
#include <QDebug>  
#include <iostream>  
#include <opencv/cv.h>  
#include <opencv/highgui.h>  
#include <opencv2/opencv.hpp>

QImage Mat2QImage(const cv::Mat&);//mat格式转换为Qimage格式  
cv::Mat QImage2Mat(const QImage);//Qimage格式转换为mat格式

#endif  