#ifndef LAPLACE_LAPLACE_H
#define LAPLACE_LAPLACE_H
#include<iostream>
#include<opencv2/highgui.hpp>
#include<cv.h>
using namespace std;
using namespace cv;
typedef uchar ty;
class Laplace {
public:
	int X_image, Y_image;
	int TempltExcute(Mat &src, int *tmplt, int tw, int x, int y);
	void SharpLaplace(Mat&src, Mat&dst);
};


#endif
