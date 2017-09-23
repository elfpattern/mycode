#include<iostream>
#include<vector>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
void ycrcb(Mat& src, Mat&dst);

int main()
{
	Mat src = imread("C:\\Users\\jingzhao004214\\Desktop\\6.jpg");
	imshow("original image", src);
	Mat dst(src.size(), CV_8UC1);
	
	ycrcb(src, dst);
	
	return 0;
	
}

void ycrcb(Mat& src, Mat&dst) 
{
	Mat srcImg;

	cvtColor(src, srcImg, CV_BGR2YCrCb);
	vector<Mat>channels;
	split(srcImg, channels);
	Mat Y, Cr, Cb;
	Y = channels.at(0);
	Cr = channels.at(1);
	Cb = channels.at(2);
	for (int j = 1; j < dst.rows - 1; j++)
	{
		uchar* currentCr = Cr.ptr<uchar>(j);
		uchar* currentCb = Cb.ptr<uchar>(j);
		uchar* current = dst.ptr<uchar>(j);
		for (int i = 0; i < dst.cols; i++)
		{
			//137, 175
			if ((currentCr[i] > 132) && (currentCr[i] < 160) && (currentCb[i] > 77) && (currentCb[i] < 127))
				current[i] = 255;
			else
				current[i] = 0;
		}
	}
	/*for (int i = 0;i < dst.rows; i++)
	{
		uchar *maskdata = mask.ptr<uchar>(i);
		Vec3b *srcdata = srcImg.ptr<Vec3b>(i);
		Vec3b *dstdata = dst.ptr<Vec3b>(i);
		for (int j = 0; j < dst.cols; j++)
		{
			if (maskdata[j] == 255)
			{
				dstdata[j] = srcdata[j];
			}
			else
				dstdata[j] = 0;

		}
	}
*/
	imshow("ycrcb", dst);
	waitKey(0);
	imwrite("ycrcb.jpg", dst);

}




