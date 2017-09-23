#include<iostream>
#include<time.h>
#include<string>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "imageWhite.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "rbf.hpp"

using namespace std;
using namespace cv;

//opencv 保存的是BGR通道
void imageWhite(unsigned char* oriImage, unsigned char* dstImage,int width,int height,int channel,int level)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dstImage[(i*width + j)*channel + 0] = whitenTable[level][oriImage[(i*width + j)*channel + 0]];
			dstImage[(i*width + j)*channel + 1] = whitenTable[level][oriImage[(i*width + j)*channel + 1]];
			dstImage[(i*width + j)*channel + 2] = whitenTable[level][oriImage[(i*width + j)*channel + 2]];	
		}
	}
}

void imageRetouch(unsigned char* oriImage, unsigned char* dstImage, int width, int height, int channel,float sigma_spatial, float sigma_range)
{
	float * buffer = new float[(width * height* channel + width * height + width * channel + width) * 2];
	recursive_bf(oriImage, dstImage, sigma_spatial, sigma_range, width, height, channel, buffer);
	delete[] buffer;
}
int main()
{
	time_t start, end;
	double totaltime;
	float sigma_spatial = 0.03;
	float sigma_range = 0.1;
	int level = 2;
	string path = "D:/work/mopi_test.jpg";
	string dstpath = "D:/work/mopi_test_resultImage.jpg";
	Mat Img = imread(path);
	Mat resImg;
	Img.copyTo(resImg);
	
	unsigned char* srcImg = Img.data;
	unsigned char* dstImg = resImg.data;
	
	int width = Img.cols;
	int height = Img.rows;
	int channel = Img.channels();
	imshow("oriImage", Img);
	imageWhite(srcImg,dstImg,width,height, channel, level);
	imshow("meibaiImage", resImg);
	imageRetouch(dstImg, dstImg,width,height,channel,sigma_spatial,sigma_range);
	imshow("meibai_mopi_Image", resImg);
	cvWaitKey(0);
	imwrite(dstpath.c_str(),resImg);
	return 0;
}
