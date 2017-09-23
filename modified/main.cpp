#include<iostream>
#include<ctime>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main(int argc, const char** argv) {
	time_t start = 0, end = 0;
	double totaltime;
	time(&start);
	Mat image;
	int c;
	cout << "please input a number between 1 and 4 to choose a picture:\n";
	cin >> c;
	switch (c)
	{
	case 1:
		image = imread("1.png");
		break;
	case 2:
		image = imread("2.jpg");
		break;
	case 3:
		image = imread("3.png");
		break;
	case 4:
		image = imread("4.jpg");
	}
	namedWindow("ĥƤǰ");
	imshow("ĥƤǰ", image);
	if (!image.empty())
	{
		Mat dst;

		int value1 = 3, value2 = 1;

		int dx = value1 * 5;    //˫���˲�����֮һ  
		double fc = value1*12.5; //˫���˲�����֮һ  
		int p = 50;//͸����  
		Mat temp1, temp2, temp3, temp4;

		//˫���˲�  
		bilateralFilter(image, temp1, dx, fc, fc);
		
		temp2 = (temp1 - image + 128);
		GaussianBlur(temp2, temp3, Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);

		temp4 = image + 2 * temp3 - 255;

		dst = (image*(100 - p) + temp4*p) / 100;
		dst.copyTo(image);
		
	}
	namedWindow("ĥƤ��");
	imshow("ĥƤ��", image);
	waitKey(0);
	time(&end);
	totaltime = double(end - start);
	cout << "��ȷ���룬���һ��������" << totaltime <<"��" << endl;
	system("pause");
	return 0;
}
