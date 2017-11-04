#pragma once
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

class Warp
{
private:
	int m_radius;
private:
	void iiw( int s, Point begin, Point end, double point_x, double point_y,
		double *src_x, double *src_y);

public:
	Warp(int r = 5);
	void warping(Mat&src, Point center, Point current);
	~Warp();
};

