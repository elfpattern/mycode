#include"emboss.h"
#include<vector>
#define Mid 128;
void zhao::emboss(Mat& src, Mat&dst)
{
	src.copyTo(dst);
	int w = src.cols;
	int h = src.rows;
	
	for (int i = 1; i < h-1; i++)
	{
		Vec3b *current = src.ptr<Vec3b>(i);
		Vec3b *next = src.ptr<Vec3b>(i + 1);
		Vec3b *dstData = dst.ptr<Vec3b>(i);
		for (int j = 1; j < w-1; j++)
		{
			dstData[j][0] = current[j][0] - next[j+1][0] + Mid;
			dstData[j][1] = current[j][1] - next[j+1][1] + Mid;
			dstData[j][2] = current[j][2] - next[j+1][2] + Mid;
		}
	}
}
