#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
void Roberts(Mat& src, Mat& dst);
int main()
{
	Mat srcImage = imread("C:\\Users\\jingzhao004214\\Desktop\\2.jpg", 0);
	namedWindow("原图");
	imshow("原图", srcImage);
	Mat dst(srcImage.size(), srcImage.type());
	Roberts(srcImage, dst);	//调用Roberts函数
	imwrite("dst.jpg", dst);
	namedWindow("效果图");
	imshow("效果图", dst);
	waitKey(0);
	return 0;
}
void Roberts(Mat& src, Mat& dst)
{
	dst = src.clone();
	int nWidth = dst.cols;
	int nHeight = dst.rows;
	uchar pixel[4];
	for (int j = 0; j < nHeight - 1; j++)
	{
		uchar* Lup = dst.ptr<uchar>(j);
		uchar* Ldown = dst.ptr<uchar>(j + 1);
		for (int i = 0; i < nWidth - 1; i++)
		{
			pixel[0] = Lup[i];
			pixel[1] = Lup[i + 1];
			pixel[2] = Ldown[i];
			pixel[3] = Ldown[i + 1];
			Lup[i] = abs(pixel[0] - pixel[3]) + abs(pixel[2] - pixel[4]);
		}
	}
}
