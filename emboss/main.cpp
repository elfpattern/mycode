#include<iostream>
#include"emboss.h"
#include<string>
using namespace std;

int main()
{
	string path = "C://Users//jingzhao004214//Desktop//3.png";
	Mat src = imread(path);
	Mat dst;
	zhao::emboss(src, dst);
	imshow("ori", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}