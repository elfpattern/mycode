#include<iostream>
#include<string>
#include"gaussian.h"
#include"Highpass.h"
#include"Retouch.h"
#include"BilateralFilter.h"
using namespace std;

int main()
{
	string path1 = "C:/Users/jingzhao004214/Desktop/xiao.jpg";
	//string path2 = "C:/Users/jingzhao004214/Desktop/boxblur1.jpg";
	Mat src = imread(path1);
	//Mat blur1 = imread(path2);
	imshow("ori",src);
	BilateralFilter filter1(5, 10, 20);//5,10,20
	Mat blur1 = filter1.filter(src);
	imshow("bilateralfilter", blur1);
	//imwrite("bilateralfilter.jpg", blur1);
	Mat dst;
	src.copyTo(dst);
	zhao::highpass(src, blur1, dst);
	//imwrite("highpass.jpg", dst);
	imshow("highpass", dst);
	Gaussian filter2(1,2);//
	Mat blur2 = filter2.filter(dst);
	imshow("gaussianfilter", blur2);
	Mat final;
	src.copyTo(final);
	jing::retouch(src, blur2, final);
	imshow("change", final);
	//imwrite("bilateralfilter.png", blur1);
	imwrite("640_320.jpg", final);
	waitKey(0);
	return 0;
}
