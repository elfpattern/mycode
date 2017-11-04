#include "Warp.h"



Warp::Warp(int r) :m_radius(r)
{
}

void Warp::iiw(int r, Point begin, Point end, double point_x, double point_y,
	double *src_x, double *src_y)
{
	double rs = m_radius;
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
		double tc =  3 * tb*tb*tb*tb - 4 * tb*tb*tb + 1;
		*src_x = point_x - tc * (end.x - begin.x);
		*src_y = point_y - tc * (end.y - begin.y);
	}
}
void Warp::warping(Mat&src, Point center, Point current)
{
	int channels = src.channels();
	int w = src.cols;
	int h = src.rows;
	uchar *buff = new uchar[4 * channels * m_radius * m_radius];
	for (int i = center.y - m_radius; i < center.y + m_radius; i++)
		for (int j = center.x - m_radius; j < center.x + m_radius; j++)
		{
			if (i >= 0 && i < h && j >= 0 && j < w)
			{
				double src_x;
				double src_y;
				iiw(m_radius, Point(center.x, center.y), Point(current.x, current.y), j, i, &src_x, &src_y);
				int pos = (i - center.y + m_radius) * 2 * channels * m_radius + (j - center.x + m_radius) * channels;
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

	for (int i = center.y - m_radius; i < center.y + m_radius; i++)
		for (int j = center.x - m_radius; j < center.x + m_radius; j++)
		{
			if (i >= 0 && i < h && j >= 0 && j < w)
			{
				uchar *p = src.data + src.step * i + j * channels;
				int pos = (i - center.y + m_radius) * 2 * channels * m_radius + (j - center.x + m_radius) * channels;
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






Warp::~Warp()
{
}
