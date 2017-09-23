#include<iostream>
#include<vector>
#include<algorithm>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
void rgb(Mat& src, Mat&dst, Mat&mask);
//void hsv(Mat& src, Mat& dst);
int main()
{
	Mat src = imread("C:\\Users\\jingzhao004214\\Desktop\\3.jpg");
	
	Mat mask(src.size(), CV_8UC1);
	Mat dst(src.size(),CV_8UC3);
	imshow("original image", src);
	waitKey(0);
	rgb(src, dst,mask);
	//hsv(src, grayImg);
	return 0;

}

void rgb(Mat& src, Mat&dst, Mat&mask)
{
	vector<Mat>channels;
	split(src, channels);
	Mat R, G, B;
	B = channels.at(0);
	G = channels.at(1);
	R = channels.at(2);
	for (int j = 0; j < dst.rows; j++)
	{
		uchar* currentR = R.ptr<uchar>(j);
		uchar* currentG = G.ptr<uchar>(j);
		uchar* currentB = B.ptr<uchar>(j);
		uchar* current = mask.ptr<uchar>(j);

		for (int i = 0; i < dst.cols; i++)
		{
			if (currentR[i] > 95 && currentG[i] > 40 && currentB[i] > 20 && abs(currentR[i] - currentG[i]) > 15 && currentR[i] > currentG[i] && currentR[i]>currentB[i] )
			{	
					current[i] = 255;
			}
			else if (currentR[i] > 220 && currentG[i] > 210 && currentB[i] > 170 && abs(currentR[i] - currentG[i]) <= 15 && currentR[i] > currentB[i])
			{
				current[i] = 255;
			}
		}
	}
	for (int j = 0; j < dst.rows; j++)
	{
		uchar* maskdata = mask.ptr<uchar>(j);
		Vec3b *srcData = src.ptr<Vec3b>(j);
		Vec3b *dstData = dst.ptr<Vec3b>(j);
		for (int i = 0; i < dst.cols; i++)
		{
			if (maskdata[i] == 255)
			{
				dstData[i][0] = srcData[i][0];
				dstData[i][1] = srcData[i][1];
				dstData[i][2] = srcData[i][2];
			}
			else
			{
				dstData[i] = 0;
			}
		}
	}

	imshow("rgb", dst);
	imwrite("rgb1.jpg", dst);
	waitKey(0);
}
//void hsv(Mat& src, Mat& dst)
//{
//	Mat hsvImg;
//	cvtColor(src, hsvImg,CV_BGR2HSV);
//	vector<Mat>channels;
//	split(src, channels);
//	Mat H;
//	H = channels.at(0);
//	for (int i = 0; i < dst.rows; i++)
//	{
//		uchar* currentH = H.ptr<uchar>(i);
//		uchar* current = dst.ptr<uchar>(i);
//		for (int j = 0; j < dst.cols; j++)
//		{
//			if (currentH[i] >= 25 && current[i] <= 50)
//				current[i] = 255;
//			else
//				current[i] = 0;
//		}
//		imshow("hsv", dst);
//		waitKey(0);
//	}
//



