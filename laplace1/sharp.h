#pragma once
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

namespace zhao  //�Լ������һ�������ռ�
{
	void sharpen(const Mat& img, Mat& result);
}
