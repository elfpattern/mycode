#ifndef __bilateral_filter__BilateralFilter__
#define __bilateral_filter__BilateralFilter__
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class BilateralFilter {
private:
	float sigmaD, sigmaC;
	int r;
	float **dw;
	float *cw;

private:
	void buildDisTable();
	void buildColorTable();
	Mat filterGrayImage(const Mat& image);
	Mat filterColorImage(const Mat& image);

public:
	BilateralFilter(int radius = 3, float sigmaD = 1.0f, float sigmaC = 1.0f);
	Mat filter(const Mat& image);
	//Mat gaussianFilter(const Mat &image);
	//Mat similarityFilter(const Mat &image);
};
#endif 