#include"sharp.h"
void sharp::sharpen(const Mat& img, Mat& result)
{
	result.create(img.size(), img.type());
	for (int row = 1; row < img.rows - 1; row++)
	{
		const uchar* previous = img.ptr<const uchar>(row - 1);
		const uchar* current = img.ptr<const uchar>(row);
		const uchar* next = img.ptr<const uchar>(row + 1);
		uchar *output = result.ptr<uchar>(row);
		int ch = img.channels();
		int starts = ch;
		int ends = (img.cols - 1) * ch;
		for (int col = starts; col < ends; col++)
		{
			*output++ = saturate_cast<uchar>(5 * current[col] - current[col - ch] - current[col + ch] - previous[col] - next[col]);
		}
	}
	result.row(0).setTo(Scalar::all(0));
	result.row(result.rows - 1).setTo(Scalar::all(0));
	result.col(0).setTo(Scalar::all(0));
	result.col(result.cols - 1).setTo(Scalar::all(0));
}