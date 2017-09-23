#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<time.h>
using namespace std;
using namespace cv;
Mat warping(Mat &src, int rMax, Point prePoint, Point endPoint);
Mat point(Mat& src, int r);
const int S = 20;//20
int main()
{
	Mat src;
	src = imread("C:\\Users\\jingzhao004214\\Desktop\\33888.jpg");
	if (!src.data)
	{
		cout << "NO DATA" << endl;
		return -1;
	}
	int r = 7;//10,8,
	Mat dst = point(src, r);
	imshow("dst", dst);
	imshow("src", src);
	imwrite("points121.jpg", dst);
	waitKey(0);
	return 0;
}
Mat point(Mat& src, int r)
{
	Point beg1, end1;
	beg1.x = 331.4732, beg1.y = 246.4582;
	end1.x = 327.2930, end1.y = 235.2110;
	Mat dst1 = warping(src, r, beg1, end1);
	Point beg2, end2;
	beg2.x = 343.1383, beg2.y = 242.8155;
	end2.x = 343.1383, end2.y = 222.8155;
	Mat dst2 = warping(dst1,r, beg2, end2);
	Point beg3, end3;
	beg3.x = 357.3478, beg3.y = 243.1783;
	end3.x = 357.3478, end3.y = 231.1783;
	Mat dst3 = warping(dst2, r, beg3, end3);
	Point beg4, end4;
	beg4.x = 332.9309, beg4.y = 256.6623;
	end4.x = 331.5080, end4.y = 268.6150;
	Mat dst4 = warping(dst3,r,beg4, end4);
	Point beg5, end5;
	beg5.x = 345.3216, beg5.y = 257.0267;
	end5.x = 345.3216, end5.y = 277.0267;
	Mat dst5 = warping(dst4,r,beg5,end5);
	return dst5;
	/*Point beg6, end6;
	beg6.x = 357.7123, beg6.y = 255.2045;
	end6.x = 360.3980, end6.y = 266.9050;
	Mat dst6 = warping(dst5,r,beg6,end6);
	return dst6;
*/
}

Mat warping(Mat &src, int rMax, Point prePoint, Point endPoint)
{
	//	cout << "起始坐标：" << prePoint << "      终止坐标： " << endPoint << endl;
	int cols = src.cols;
	int rows = src.rows;
	Mat mask = Mat(Size(cols, rows), CV_8UC1, Scalar(0, 0, 0));
	Mat result = Mat(Size(cols, rows), CV_8UC3, Scalar(0, 0, 0));
	double x = 0, y = 0;
	for (int i = prePoint.y - rMax; i < prePoint.y + rMax;++i)
	{
		uchar  *data = mask.ptr<uchar>(i);
		for (int j = prePoint.x - rMax; j < prePoint.x + rMax; ++j)
		{

			double r = sqrt((i - prePoint.y)*(i - prePoint.y) + (j - prePoint.x)*(j - prePoint.x));
			if (r <= rMax && i >= 0 && j >= 0 && i < rows && j < cols)
			{

				data[j] = 255;
				double temp1 = r*r;
				double temp2 = 1.0*(endPoint.x - prePoint.x)* (endPoint.x - prePoint.x)
					+ 1.0*(endPoint.y - prePoint.y)* (endPoint.y - prePoint.y);

				double temp = 1.0*(rMax*rMax - temp1) / (rMax*rMax - temp1 + (100.0 / S)*temp2);

				x = j - (endPoint.x - prePoint.x)*temp*temp;
				y = i - (endPoint.y - prePoint.y)*temp*temp;

				int x1 = (int)x;
				int y1 = (int)y;
				int x2 = x1 + 1;
				int y2 = y1 + 1;

				Vec3b src1 = src.at<Vec3b>(y1, x1);
				Vec3b src2 = src.at<Vec3b>(y1, x2);
				Vec3b src3 = src.at<Vec3b>(y2, x1);
				Vec3b src4 = src.at<Vec3b>(y2, x2);

				Vec3d up, down;
				up[0] = (double)(src1[0] * (x - x1) + src2[0] * (x2 - x));
				up[1] = (double)(src1[1] * (x - x1) + src2[1] * (x2 - x));
				up[2] = (double)(src1[2] * (x - x1) + src2[2] * (x2 - x));


				down[0] = (double)(src3[0] * (x - x1) + src4[0] * (x2 - x));
				down[1] = (double)(src3[1] * (x - x1) + src4[1] * (x2 - x));
				down[2] = (double)(src3[2] * (x - x1) + src4[2] * (x2 - x));


				result.at<Vec3b>(i, j)[0] = (cvRound)(up[0] * (y - y1) + down[0] * (y2 - y));
				result.at<Vec3b>(i, j)[1] = (cvRound)(up[1] * (y - y1) + down[1] * (y2 - y));
				result.at<Vec3b>(i, j)[2] = (cvRound)(up[2] * (y - y1) + down[2] * (y2 - y));

				//cout << "(" << j << "," << i << ")   " << "(" << x << "," << y << ")   "<<endl;
			}
		}
	}

	for (int i = 0; i < rows;++i)
	{
		uchar * maskData = mask.ptr<uchar>(i);
		Vec3b * srcData = src.ptr<Vec3b>(i);
		Vec3b * dstData = result.ptr<Vec3b>(i);
		for (int j = 0; j < cols;++j)
		{
			if (maskData[j] == 255)
				continue;
			dstData[j] = srcData[j];
		}
	}
	return result;

}

