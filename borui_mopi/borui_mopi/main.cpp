#include<iostream>
#include"USM.h"


using namespace std;

// 查表进行gamma校正
float GammaLUT[256];
void buildTable(float fprecompensation)
{
	float f;
	for (int i = 0; i < 256; i++)
	{
		f = i / 255.0;
		f = 1.0*pow(f, fprecompensation);
		GammaLUT[i] = f;
		//GammaLUT[i] = uchar(f*255-0.5);
	}
}

int main()
{
	//分母越大对比度越明显
	buildTable(0.90);
	string path1 = "C:/Users/jingzhao004214/Desktop/a.jpg";
	Mat srcImg = imread(path1);
	int h = srcImg.rows;
	int w = srcImg.cols;
	cv::imshow("original", srcImg);

	//手机上是这么处理的..........
	//一系列的图像的精度变换
	Mat curveImg(srcImg.size(), CV_32FC3);
	Mat_<float> blenImg(srcImg.size(), CV_32FC1);
	Mat NormalizeImg;
	srcImg.convertTo(NormalizeImg, CV_32FC3, 1 / 255.0);
	Mat Exposure;
	NormalizeImg.convertTo(Exposure, CV_32FC3, pow(2.0, -1.0));
	
	for (int i = 0; i < h; i++)
	{
		
		float *ptr = Exposure.ptr<float>(i);
		float *ptr2 = curveImg.ptr<float>(i);
		uchar *ptr3 = srcImg.ptr<uchar>(i);
		for (int j = 0; j < w; j++)
		{
			float mask = 2.0*ptr[3 * j] * ptr[3 * j + 1];
			//float mask = 0.114*ptr1[3 * j] + 0.587*ptr1[3 * j + 1] + 0.299*ptr1[3*j+2];
			blenImg[i][j] = mask;

			int b = ptr3[3 * j];
			int g = ptr3[3 * j + 1];
			int r = ptr3[3 * j + 2];
			//ptr2[3 * j] = spline[b]/255.0;
			//ptr2[3 * j + 1] = spline[g] /255.0;
			//ptr2[3 * j + 2] = spline[r] /255.0;
			ptr2[3 * j] = GammaLUT[b];
			ptr2[3 * j + 1] = GammaLUT[g];
			ptr2[3 * j + 2] = GammaLUT[r];
		}
	}//进行gamma曲线的增强

	float sigmaD = 15.0;
	float sigmaC = (1 / (2 * 3.1415926*sigmaD*sigmaD));
	int r = 7;
	float **dw, *cw;
	cw = new float[256];
	dw = new float *[2 * r + 1];
	for (int i = 0; i < 2 * r + 1; i++)
		dw[i] = new float[2 * r + 1];
	for (int i = -r; i <= r; i++) {
		for (int j = -r; j <= r; j++) {
			//dw[i + r][j + r] = 1.0 / ((2 * r + 1)*(2 * r + 1));
			dw[i + r][j + r] = sigmaC*exp(-0.5*(i*i + j*j) / (sigmaD*sigmaD));
		}
	}
	//for (int i = 0; i < 256; i++) {
	//	float j = i / 255.0;
	//	cw[i] = exp(-0.5 * (i*i) / (sigmaC*sigmaC));
	//}

	Mat_<float> BFImg(srcImg.size(), CV_32FC1);
	Mat_<float> highpass(srcImg.size(), CV_32FC1);

	// bilateral filter
	//#pragma omp parallel for
	for (int row = r; row < h - r; row++)
	{
		//float *ptr1 = NormalizeImg.ptr<float>(row);
		float *ptr2 = highpass.ptr<float>(row);
		for (int col = r; col < w - r; col++)
		{
			float weightSum = 0;
			float pixelSum = 0;
			float cur_pixel = blenImg[row][col];

			for (int i = -r; i <= r; i++)
			{
				for (int j = -r; j <= r; j++)
				{
					float weight;
					float nei_pixel = blenImg[row + i][col + j];

					//float Itensitive = exp(-0.5 * ((nei_pixel - cur_pixel)*(nei_pixel - cur_pixel)) / (sigmaC*sigmaC));
					float a = sqrt((nei_pixel - cur_pixel)*(nei_pixel - cur_pixel) * 3) * 5;
					float Itensitive = fmin(a, 1.0);
					float Spatial = dw[i + r][j + r];
					weight = Spatial * (1 - Itensitive);
					pixelSum += nei_pixel * weight;
					weightSum += weight;
				}
			}

			float res = pixelSum / weightSum;
			BFImg[row][col] = res;
			// enhance three times
			float delta = cur_pixel - res + 0.5;
			for (int k = 0; k < 6; k++)
			{
				if (delta < 0.5)
					delta = delta*delta * 2;
				else
					delta = 1.0 - (1.0 - delta)*(1.0 - delta) * 2;
			}
			const float temp = 255.0 / (164.0 - 75.0);
			delta = (delta - 75.0 / 255.0)*temp;

			if (delta < 0.0) delta = 0.0;
			if (delta > 1.0) delta = 1.0;

			highpass[row][col] = delta;
		}
	}

	//blur(highpass, highpass, Size(5,5));

	Mat combine(srcImg.size(), CV_32FC3);
	for (int i = 0; i < h; i++)
	{
		float *ptr = curveImg.ptr<float>(i);
		float *ptr2 = NormalizeImg.ptr<float>(i);
		float *ptr3 = combine.ptr<float>(i);
		for (int j = 0; j < w; j++)
		{
			float alpha = highpass[i][j];
			ptr3[3 * j + 0] = ((1 - alpha)*ptr[3 * j] + alpha*ptr2[3 * j]);
			ptr3[3 * j + 1] = ((1 - alpha)*ptr[3 * j + 1] + alpha*ptr2[3 * j + 1]);
			ptr3[3 * j + 2] = ((1 - alpha)*ptr[3 * j + 2] + alpha*ptr2[3 * j + 2]);
		}
	}
	imshow("meiyan", combine);

	Mat sharpness = ruihua::USM(combine);
	imshow("sharpness", sharpness);

	waitKey(0);
	delete[]cw;
	delete[]dw;
	return 0;
}