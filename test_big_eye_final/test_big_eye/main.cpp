#include<iostream>
#include"Warp.h"
using namespace std;

int main()
{
	Mat src = imread("C:/Users/jingzhao004214/Desktop/33888.jpg");
	imshow("ori", src);
	int r= 20;
	int s = 10;
	//做眼睛，取瞳孔中心点0
	Point center_left = Point(346.0505, 250.4669);
	Warp left_eye(r,s);
	left_eye.warping(src, center_left);
	imshow("big_eye1", src);

	//右眼睛，取瞳孔中心9
	Point center_right = Point(453.1933, 231.5165);
	Warp right_eye(r, s);
	right_eye.warping(src, center_right);
	imshow("big_eye2", src);

	waitKey(0);
	return 0;
}

