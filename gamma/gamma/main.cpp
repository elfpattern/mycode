
//typedef unsigned char U8;
//U8 g_GammaLUT[256];
//
//void BulidTable(float fPrecompensation)
//{
//	float f;
//	for (int i = 0; i < 256; i++)
//	{
//		f = (i + 0.5F) / 256;
//		f = (float)pow(f, fPrecompensation);
//		g_GammaLUT[i] = (U8)(f * 256 - 0.5F);
//	}
//}

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<string>

using namespace cv; //下面的所有cv相关类型不用加上前缀了
using namespace std;

int main()
{
	string path = "C:/Users/jingzhao004214/Desktop/a.jpg";
	Mat img = imread(path);
	Mat& src = img;
	imshow("ori", src);
	Mat& MyGammaCorrection(Mat& src, float fGamma);
	if (!img.data)
		return -1;
	float fGamma = 1 / 2.2;//2.2
	MyGammaCorrection(img, fGamma);
	
	imshow("dst", src);
	imwrite("gamma.jpg",src);
	waitKey(0);
	return 0;
}


Mat& MyGammaCorrection(Mat& src, float fGamma)
{
	CV_Assert(src.data);  //若括号中的表达式为false，则返回一个错误的信息。

						  // accept only char type matrices  
	CV_Assert(src.depth() != sizeof(uchar));
	// build look up table  
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		lut[i] = pow((float)(i / 255.0), fGamma) * 255.0;
	}
	//先归一化，i/255,然后进行预补偿(i/255)^fGamma,最后进行反归一化(i/255)^fGamma*255

	const int channels = src.channels();
	switch (channels)
	{
	case 1:
	{
		//运用迭代器访问矩阵元素
		MatIterator_<uchar> it, end;
		for (it = src.begin<uchar>(), end = src.end<uchar>(); it != end; it++)
			//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;  
			*it = lut[(*it)];

		break;
	}
	case 3:
	{

		MatIterator_<Vec3b> it, end;
		for (it = src.begin<Vec3b>(), end = src.end<Vec3b>(); it != end; it++)
		{
			//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;  
			//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;  
			//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;  
			(*it)[0] = lut[((*it)[0])];
			(*it)[1] = lut[((*it)[1])];
			(*it)[2] = lut[((*it)[2])];
		}

		break;

	}
	}

	return src;
}

