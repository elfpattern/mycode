#include"USM.h"
Mat ruihua::USM(Mat img)
{
	int **dw;
	Mat mask(img.size(), CV_8UC3);

	int h = img.rows;
	int w = img.cols;

	dw = new int*[2 * 1 + 1];
	for (int i = 0; i < 2 * 1 + 1; i++)
		dw[i] = new int[2 * 1 + 1];
	dw[0][0] = -1; dw[0][1] = -1; dw[0][2] = -1;
	dw[1][0] = -1; dw[1][1] = 8; dw[1][2] = -1;
	dw[2][0] = -1; dw[2][1] = -1; dw[2][2] = -1;

	for (int row = 1; row < h - 1; row++)
	{
		for (int col = 1; col < w - 1; col++)
		{
			float pixsum[3] = { 0, };
			//Vec3f cur = img.at<Vec3f>(row, col);
			Vec3b cur = img.at<Vec3b>(row, col);

			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
				{
					Vec3b nei = img.at<Vec3b>(row + i, col + j);
					for (int c = 0; c < 3; c++)
					{
						pixsum[c] += nei[c] * dw[i + 1][j + 1];
					}
				}
			for (int c = 0; c < 3; c++)
				cur[c] = saturate_cast<uchar>(1 * (0.1*pixsum[c] + cur[c]));
			mask.at<Vec3b>(row, col) = cur;

		}
	}
	return mask;



}