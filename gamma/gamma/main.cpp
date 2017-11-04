
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

using namespace cv; //���������cv������Ͳ��ü���ǰ׺��
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
	CV_Assert(src.data);  //�������еı��ʽΪfalse���򷵻�һ���������Ϣ��

						  // accept only char type matrices  
	CV_Assert(src.depth() != sizeof(uchar));
	// build look up table  
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		lut[i] = pow((float)(i / 255.0), fGamma) * 255.0;
	}
	//�ȹ�һ����i/255,Ȼ�����Ԥ����(i/255)^fGamma,�����з���һ��(i/255)^fGamma*255

	const int channels = src.channels();
	switch (channels)
	{
	case 1:
	{
		//���õ��������ʾ���Ԫ��
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

