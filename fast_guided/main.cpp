#include<iostream>
#include<string>
#include"fast_guided_filter.h";
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{
	string path = "C://Users//jingzhao004214//Desktop//0.jpg";
	Mat src = imread(path);
	Mat guidance;
	Mat dst;
	guidance.copyTo(src);
	dst.copyTo(dst);
	unsigned char* pSrc = src.data;
	unsigned char* pGuidance = guidance.data;
	unsigned char* pDst = dst.data;
	int w = src.cols;
	int h = src.rows;
	int c = 1;
	int r = 4;
	float rp = 0.01;
	float sr = 4;

	fast_guided_filter(pSrc, pGuidance, pDst, w, h, c, r, rp, sr);


	return 0;
}
