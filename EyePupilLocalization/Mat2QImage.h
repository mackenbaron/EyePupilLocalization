#ifndef MAT2QIMAGE_H  
#define MAT2QIMAGE_H  

#include <QtGui>  
#include <QDebug>  
#include <iostream>  
#include <opencv/cv.h>  
#include <opencv/highgui.h>  

QImage Mat2QImage(const cv::Mat&);//mat格式转换为Qimage格式  

#endif  