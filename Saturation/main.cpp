
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;


void SaturationAdjustRGB(unsigned char *pSrc, unsigned char *pDest, int nWidth, int nHeight, int nParameter);
int main()
{
	string path = "C://Users//jingzhao004214//Desktop//33.jpg";
	Mat src = imread(path);
	if (src.empty())
	{
		return -1;
	}
	int w = src.cols;
	int h = src.rows;
	Mat dst;
	src.copyTo(dst);
	
	unsigned char *pSrc = src.data;
	unsigned char *pDst = dst.data;
	int parameter = 50;
	SaturationAdjustRGB(pSrc, pDst, w, h, parameter);
	imshow("ori", src);
	imshow("saturation", dst);
	waitKey(0);

	return 0;
}

void SaturationAdjustRGB(unsigned char *pSrc, unsigned char *pDest, int nWidth, int nHeight, int nParameter)
{
	int i = 0;
	int t = 0;
	int nLength = nHeight * nWidth;
	cout << nLength << endl;

	//��������  
	double dPercent = static_cast< double >(nParameter) / 100;

	//RGB��ɫͨ������  

	unsigned char *imgR = new unsigned char[nLength];
	unsigned char *imgG = new unsigned char[nLength];
	unsigned char *imgB = new unsigned char[nLength];

	//�ֲ���������  
	unsigned char rgbMax;
	unsigned char rgbMin;
	double  dDelta;
	double  dValue;
	double  dL;
	double  dS;
	double  dAlpha;

	//�����RGBͨ��  
	for ( i = 0; i < nLength; i++)
	{
		t = 3 * i;
		imgB[i] = pSrc[t];
		imgG[i] = pSrc[t + 1];
		imgR[i] = pSrc[t + 2];
	}

	for (int i = 0; i < nLength; i++)
	{
		rgbMax = max(max(imgR[i], imgG[i]), imgB[i]);
		rgbMin = min(min(imgR[i], imgG[i]), imgB[i]);

		dDelta = static_cast<double>(rgbMax - rgbMin) / 255;
		dValue = static_cast<double>(rgbMax + rgbMin) / 255;

		//��������ص��ǻ�ɫ ������  
		if (0 == dDelta)
		{
			continue;
		}

		//���չ�ʽ��������L   [0,1]  
		dL = dValue / 2;

		//���չ�ʽ���㱥�Ͷ�S   [0,1]  
		if (dL < 0.5)
		{
			dS = dDelta / dValue;
		}
		else
		{
			dS = dDelta / (2 - dValue);
		}

		//���б��Ͷȵ���  
		if (dPercent >= 0)
		{
			if (dPercent + dS >= 1)
			{
				dAlpha = dS;
			}
			else
			{
				dAlpha = 1 - dPercent;
			}
			dAlpha = 1 / dAlpha - 1;
			imgB[i] = imgB[i] + (imgB[i] - dL * 255) * dAlpha;
			imgG[i] = imgG[i] + (imgG[i] - dL * 255) * dAlpha;
			imgR[i] = imgR[i] + (imgR[i] - dL * 255) * dAlpha;
		}
		else
		{
			dAlpha = dPercent;
			imgB[i] = dL * 255 + (imgB[i] - dL * 255) * (1 + dAlpha);
			imgG[i] = dL * 255 + (imgG[i] - dL * 255) * (1 + dAlpha);
			imgR[i] = dL * 255 + (imgR[i] - dL * 255) * (1 + dAlpha);
		}
	}

	//�õ����  
	for (i = 0; i < nLength; i++)
	{
		t = 3 * i;
		pDest[t] = imgB[i];
		pDest[t + 1] = imgG[i];
		pDest[t + 2] = imgR[i];
	}
	//�ͷ��ڴ�  
	if (!imgR)
	{
		delete[]imgR;
		imgR = NULL;
	}
	if (!imgG)
	{
		delete[]imgG;
		imgG = NULL;
	}
	if (!imgB)
	{
		delete[]imgB;
		imgB = NULL;
	}

}