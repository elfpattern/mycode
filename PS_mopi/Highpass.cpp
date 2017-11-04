#include "Highpass.h"

void zhao::highpass(Mat& src, Mat&temp, Mat& dst)
{
	int h = src.rows;
	int w = src.cols;

	for (int i = 0; i < h; i++)
	{
		const uchar* current1 = src.ptr<uchar>(i);
		const uchar* current2 = temp.ptr<uchar>(i);
		uchar* output = dst.ptr<uchar>(i);
		int ch = src.channels();
		int ends = w * ch;
		for (int j = 0; j < ends; j++)
		{
			*output++ = saturate_cast<uchar>(current2[j] - current1[j] + 128);
		}
	}
}




