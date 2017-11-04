#pragma once
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
namespace jing {
	void retouch(Mat& src, Mat& blur, Mat& dst);
}