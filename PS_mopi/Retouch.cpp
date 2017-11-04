#include "Retouch.h"
#include<iostream>
using namespace std;
void jing::retouch(Mat& src, Mat& blur, Mat& final)
{
	int h = src.rows;
	int w = src.cols;

	for (int i = 0; i < h; i++)
	{
		const uchar* cur1 = src.ptr<uchar>(i);
		const uchar* cur2 = blur.ptr<uchar>(i);
		uchar* output = final.ptr<uchar>(i);
		int ch = src.channels();
		int ends = w * ch;
		for (int j = 0; j < ends; j++)
		{
			//*output++ = saturate_cast<uchar>(cur1[j] + 2 * cur2[j] - 256);
			int opt = 50;

			*output++ = saturate_cast<uchar>(((cur1[j]*(100-opt))+(cur1[j] + 2 * cur2[j] - 200)*opt)/100);//256
		}
	}
}

