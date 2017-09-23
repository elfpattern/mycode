#include <opencv2/highgui/highgui.hpp>
//#pragma comment(lib, "opencv_core2413d.lib")
//#pragma comment(lib, "opencv_highgui2413d.lib")
//#pragma comment(lib, "opencv_imgproc2413d.lib")
using namespace cv;
#include<time.h>
#include<iostream>
#include "sharp.h"
using namespace std;
int main()
{
	Mat lena = imread("C:\\Users\\jingzhao004214\\Desktop\\33.jpg");
	Mat sharpenedLena;
	clock_t start, end;
	double totaltime;
	start = clock();
	zhao::sharpen(lena, sharpenedLena);
	end = clock();
	totaltime = end - start;
	cout << "cost time:" << totaltime << "ms" << endl;
	imshow("lena", lena);
	imshow("sharpened lena", sharpenedLena);
	cvWaitKey(0);
	return 0;
}