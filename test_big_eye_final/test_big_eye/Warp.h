#pragma once
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

class Warp
{
private:
	int m_radius;
	int m_strength;
private:
	void iiw( Point begin, double point_x, double point_y,
		double *src_x, double *src_y);

public:
	Warp(int r = 5, int S = 10);
	void warping(Mat&src, Point center);
	~Warp();
};
