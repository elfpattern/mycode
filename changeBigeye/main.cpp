#include<iostream>
#include<string>
#include<vector>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
void iiw(int radius, int strength, Point begin, Point end, double point_x, double point_y,
	double *src_x, double *src_y);
void warping(Mat&src, Point end, Point current, int r, int strength);
int main()
{
	string path = "C:\\Users\\jingzhao004214\\Desktop\\33888.jpg";
	Mat src = imread(path);
	imshow("ori", src);
	int strength = 20; //10
	//5
	int r = 15;
	Point begin1 = Point(331, 246);
	Point end1 = Point(330, 242); 
	warping(src, begin1, end1, r, strength);

	//3
	
	Point beg1 = Point(343, 242);
	Point fin1 = Point(343, 237);
	warping(src, beg1, fin1, r, strength);

	//7
	
	Point begin2 = Point(357, 243);
	Point end2 = Point(359, 238);
	warping(src, begin2, end2, r, strength);

	//6

	Point beg2 = Point(333, 257);
	Point fin2 = Point(332, 261);
	warping(src, beg2, fin2, r, strength);

	//4
	
	Point beg3 = Point(345, 257);
	Point fin3 = Point(345, 262);
	warping(src, beg3, fin3, r, strength);

	//8
	Point begin4 = Point(357, 255);
	Point end4 = Point(359, 260);
	warping(src, begin4, end4, r, strength);

	//14
	Point beg4 = Point(441, 231);
	Point fin4 = Point(438, 227);
	warping(src, beg4, fin4, r, strength);

	//12
	Point beg5 = Point(453, 225);
	Point fin5 = Point(453, 220);
	warping(src, beg5, fin5, r, strength);

	//16
	Point begin16 = Point(446, 225);
	Point end16 = Point(446, 220);
	warping(src, begin16, end16, r, strength);

	//15
	Point begin15 = Point(443, 242);
	Point end15 = Point(444, 247);
	warping(src, begin15, end15, r, strength);

	//13
	Point begin13 = Point(457, 240);
	Point end13 = Point(457, 245);
	warping(src, begin13, end13, r, strength);

	 //17
	Point beg6 = Point(468, 235);
	Point fin6 = Point(471, 239);
	warping(src, beg6, fin6, r, strength);

	imshow("bigeye", src);
	//imwrite("14.jpg", src);
	waitKey(0);
	return 0;
	}


void iiw(int radius, int strength, Point begin, Point end, double point_x, double point_y,
	double *src_x, double *src_y)
{
		double rs = radius;
		double xc = sqrt((point_x - begin.x)*(point_x - begin.x)
			+ (point_y - begin.y)*(point_y - begin.y));
		if (rs < xc)
		{
			*src_x = point_x;
			*src_y = point_y;
		}
		else
		{
			double tb = xc / rs;
			double tc = strength / 50.0 * (3 * tb*tb*tb*tb - 4 * tb*tb*tb + 1);
			*src_x = point_x - tc * (end.x - begin.x);
			*src_y = point_y - tc * (end.y - begin.y);
		}
	}

void warping(Mat&src, Point end, Point current, int r, int strength)
{
	int channels = src.channels();
	int w = src.cols;
	int h = src.rows;
	uchar *buff = new uchar[4 * channels * r * r];
	for (int i = end.y - r; i < end.y + r; i++)
		for (int j = end.x - r; j < end.x + r; j++)
		{
			if (i >= 0 && i < h && j >= 0 && j < w)
			{
				double src_x;
				double src_y;
				iiw(r, strength, Point(end.x, end.y), Point(current.x, current.y), j, i, &src_x, &src_y);
				int pos = (i - end.y + r) * 2 * channels * r + (j - end.x + r) * channels;
				if (src_x >= 0 && src_x < w - 1
					&& src_y >= 0 && src_y < h - 1)
				{
					int x1 = src_x;
					int y1 = src_y;
					double t = src_x - x1;
					double u = src_y - y1;

					if (channels == 3)
					{
						uchar *p = src.data + src.step * y1 + x1 * channels;
						uchar b1 = *p;
						uchar g1 = *(p + 1);
						uchar r1 = *(p + 2);
						uchar b2 = *(p + 3);
						uchar g2 = *(p + 4);
						uchar r2 = *(p + 5);
						p = src.data + src.step * (y1 + 1) + x1 * channels;
						uchar b3 = *p;
						uchar g3 = *(p + 1);
						uchar r3 = *(p + 2);
						uchar b4 = *(p + 3);
						uchar g4 = *(p + 4);
						uchar r4 = *(p + 5);

						buff[pos] = (1 - t)*(1 - u)*b1 + t*(1 - u)*b2 + (1 - t)*u*b3 + t*u*b4;
						buff[pos + 1] = (1 - t)*(1 - u)*g1 + t*(1 - u)*g2 + (1 - t)*u*g3 + t*u*g4;
						buff[pos + 2] = (1 - t)*(1 - u)*r1 + t*(1 - u)*r2 + (1 - t)*u*r3 + t*u*r4;
					}
					else
					{
						uchar *p = src.data + src.step * y1 + x1 * channels;//pImg
						uchar b1 = *p;
						uchar b2 = *(p + 1);
						p = src.data + src.step * (y1 + 1) + x1 * channels;//pImg
						uchar b3 = *p;
						uchar b4 = *(p + 1);

						buff[pos] = (1 - t)*(1 - u)*b1 + t*(1 - u)*b2 + (1 - t)*u*b3 + t*u*b4;
					}
				}
				else
				{
					if (channels == 3)
					{
						buff[pos] = 0;
						buff[pos + 1] = 0;
						buff[pos + 2] = 0;
					}
					else
					{
						buff[pos] = 0;
					}
				}
			}
		}

	for (int i = end.y - r; i < end.y + r; i++)
		for (int j = end.x - r; j < end.x + r; j++)
		{
			if (i >= 0 && i < h && j >= 0 && j < w)
			{
				uchar *p = src.data + src.step * i + j * channels; 
				int pos = (i - end.y + r) * 2 * channels * r + (j - end.x + r) * channels;
				*p = buff[pos];
				if (channels == 3)
				{
					*(p + 1) = buff[pos + 1];
					*(p + 2) = buff[pos + 2];
				}
			}

		}
	delete[] buff;
}