#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
class Gaussian
{
private:
	int r;
	float sigmaD;
	float **dw;
private:
	void buliDisTable();
	Mat filterColorImage(const Mat& image);
public:
	Gaussian(int radius = 1.0f, float sigmaD =1.0f );
	Mat filter(const Mat& image);
	~Gaussian();
};

