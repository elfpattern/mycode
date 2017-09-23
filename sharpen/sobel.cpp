
int main(int argc, char *argv[])
{
	Mat image = imread(argv[1], 0);
	Mat imageX = Mat::zeros(image.size(), CV_16SC1);
	Mat imageY = Mat::zeros(image.size(), CV_16SC1);
	Mat imageXY = Mat::zeros(image.size(), CV_16SC1);
	Mat imageX8UC;
	Mat imageY8UC;
	Mat imageXY8UC;
	if (!image.data)
	{
		return  - 1;
	}
	GaussianBlur(image, image, Size(3, 3), 0); //高斯滤波消除噪点  
	uchar *P = image.data;
	uchar *PX = imageX.data;
	uchar *PY = imageY.data;
	int step = image.step;
	int stepXY = imageX.step;
	for (int i = 1;i<image.rows - 1;i++)
	{
		for (int j = 1;j<image.cols - 1;j++)
		{
			//通过指针遍历图像上每一个像素  
			PX[i*imageX.step + j*(stepXY / step)] = abs(P[(i - 1)*step + j + 1] + P[i*step + j + 1] * 2 + P[(i + 1)*step + j + 1] - P[(i - 1)*step + j - 1] - P[i*step + j - 1] * 2 - P[(i + 1)*step + j - 1]);
			PY[i*imageX.step + j*(stepXY / step)] = abs(P[(i + 1)*step + j - 1] + P[(i + 1)*step + j] * 2 + P[(i + 1)*step + j + 1] - P[(i - 1)*step + j - 1] - P[(i - 1)*step + j] * 2 - P[(i - 1)*step + j + 1]);
		}
	}
	addWeighted(imageX, 0.5, imageY, 0.5, 0, imageXY);//融合X、Y方向    
	convertScaleAbs(imageX, imageX8UC);
	convertScaleAbs(imageY, imageY8UC);
	convertScaleAbs(imageXY, imageXY8UC);   //转换为8bit图像  

	Mat imageSobel;
	Sobel(image, imageSobel, CV_8UC1, 1, 1); //Opencv的Sobel函数  

	imshow("Source Image", image);
	imshow("X Direction", imageX8UC);
	imshow("Y Direction", imageY8UC);
	imshow("XY Direction", imageXY8UC);
	imshow("Opencv Soble", imageSobel);
	waitKey();
	return 0;
}

