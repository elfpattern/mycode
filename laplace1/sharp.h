#pragma once
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

namespace zhao  //自己定义的一个命名空间
{
	void sharpen(const Mat& img, Mat& result);
}
