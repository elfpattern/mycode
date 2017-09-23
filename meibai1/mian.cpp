#include<iostream>
#include<ctime>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;
void imageWhite(Mat& src, Mat&dst, int level);
int main()
{
	int a = 0;
	cout << "please input the level of whiten:" << endl;
	cin >> a;
	Mat src = imread("C:\\Users\\jingzhao004214\\Desktop\\2.jpg");
	Mat dst(src.size(), CV_32FC3);
	imageWhite( src,dst,a);
	system("pause");
	return 0;
}
void imageWhite(Mat& src,Mat& dst, int level)
{
	int whitelevel = level;
	int n[] = { 1,2,3,4,7,10,13,16,19,22,25,28 };
	for (int i = 0; i <= 12; i++)
	{
		if (level == n[i])
		{
			//Mat dst(src.size(), CV_32FC3);
			for (int j = 0; j < src.rows; j++)
			{
				for (int k = 0; k < src.cols; k++)
				{
					dst.at<Vec3f>(j, k)[0] = log(n[i] + src.at<Vec3b>(j, k)[0]);
					dst.at<Vec3f>(j, k)[1] = log(n[i] + src.at<Vec3b>(j, k)[1]);
					dst.at<Vec3f>(j, k)[2] = log(n[i] + src.at<Vec3b>(j, k)[2]);
				}
			}
			normalize(dst, dst, 0, 255, CV_MINMAX);
			convertScaleAbs(dst, dst); //使用线性变换转换输入数组元素成8位无符号整型
			int a = n[i];
			string s = to_string(a);
			imwrite(s + ".jpg", dst);
			imshow("whiten", dst);
			waitKey(0);
		}
	}
}
