#include "gaussian.h"
#define pi 3.1415926


Gaussian::Gaussian(int radius, float sigmaD):r(radius),sigmaD(sigmaD)
{
	this->dw = new float*[2 * radius + 1];
	for (int i = 0; i < 2 * radius + 1; i++)
	{
		this->dw[i] = new float[2 * radius + 1];
	}
	buliDisTable();
}
void Gaussian::buliDisTable() {
	float temp = 1 / (2 * pi*sigmaD*sigmaD);
	for (int i = -r; i <= r; i++)
	{
		for (int j = -r; j <= r; j++)
		{
			dw[i + r][j + r] = temp * exp(-0.5*(i*i + j*j) / (sigmaD*sigmaD));
		}
	}
}
Mat Gaussian::filterColorImage(const cv::Mat &image) {
	assert(image.channels() == 3);
	Mat ret;
	image.copyTo(ret);

	for (int row = r; row < image.rows - r; row++) {

		for (int col = r; col < image.cols - r; col++) {

			float weightSum[3] = { 0, };

			float pixelSum[3] = { 0, };

			Vec3b cur = image.at<Vec3b>(row, col);

			for (int i = -r; i <= r; i++) {

				for (int j = -r; j <= r; j++) {

					// RGB channel

					Vec3b neighbor = image.at<Vec3b>(row + i, col + j);

					for (int c = 0; c < image.channels(); c++) {

						float weight = dw[i + r][j + r] ;

						pixelSum[c] += neighbor[c] * weight;

						weightSum[c] += weight;

					}

				}

			}

			for (int c = 0; c < image.channels(); c++) {

				cur[c] = pixelSum[c] / weightSum[c];

			}
			ret.at<Vec3b>(row, col) = cur;
		}

	}

	return ret;

}

Mat Gaussian::filter(const Mat&image)
{
	if (image.channels() == 3)
	{
		cout << "blur color image" << endl;
		return filterColorImage(image);
	}
	else
	{
		cout << "it is wrong" << endl;
	}	
}
Gaussian::~Gaussian()
{
}
