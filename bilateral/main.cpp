#include <iostream>
#include<time.h>
#include <opencv2/opencv.hpp>
#include "BilateralFilter.h"
using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
	clock_t start1, start2, end1, end2;
	double totaltime1, totaltime2;
	Mat image = imread("C:\\Users\\jingzhao004214\\Desktop\\2.jpg");
	Mat filteropencv;
	start1 = clock();
	bilateralFilter(image, filteropencv, 7, 10, 10);
	end1 = clock();
	totaltime1 = double(end1 - start1);
	cout << "the time of opencv:" << totaltime1 << endl;
	BilateralFilter filter(3, 10, 10);
	start2 = clock();
	Mat blur = filter.filter(image);
	end2 = clock();
	totaltime2 = double(end2 - start2);
	cout << "the time of own :" << totaltime2 << endl;
	imshow("opencv", filteropencv);
	imshow("blur", blur);
	imwrite("blur3.jpg", blur);
	waitKey(0);
	system("pause");
	return 0;

}