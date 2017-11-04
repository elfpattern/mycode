#pragma once
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

namespace sharp
{

	void sharpen(const Mat& img, Mat& result);

}
