#include "laplace.h"
/**

* ���ܣ�ʹ��ģ��ԻҶ�ͼ��������д���

* ������srcΪĿ��ͼ��tmpltΪģ�壬twΪ�����С��x,yΪҪȡ�����ص�����

*/

int Laplace::TempltExcute(Mat &src, int *tmplt, int tw, int x, int y) {
	int i, j, py, px;
	int sum = 0;
	for (i = 0;i<tw;i++) {
		for (j = 0;j<tw;j++) {
			py = y - tw / 2 + i;
			px = x - tw / 2 + j;
			sum += src.at<ty>(py, px)*tmplt[i*tw + j];
		}
	}
	return sum;
}

void Laplace::SharpLaplace(Mat &src, Mat&dst) {
	int tmplt[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	int scale = 3;
	int tmp;

	for (int h = 1;h < Y_image - 1;h++) {
		for (int w = 1;w < X_image - 1;w++) {
			tmp = TempltExcute(src, tmplt, 3, w, h);
			tmp = tmp / scale;//�����񻯳̶ȣ�
			tmp = tmp + src.at<ty>(h, w);

			tmp = tmp > 255 ? 255 : tmp;
			tmp = tmp < 0 ? 0 : tmp;
			dst.at<ty>(h, w) = tmp;
		}
	}
}



int main() {
	Mat src, dst;
	string filename = "C:\\Users\\jingzhao004214\\Desktop\\simi_blur.jpg";
	src = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	dst.create(src.size(), src.type());
	Laplace p;
	p.X_image = src.cols;
	p.Y_image = src.rows;
	p.SharpLaplace(src, dst);
	//cvtColor(dst, dst, CV_GRAY2BGR);
	namedWindow("origin");
	namedWindow("result");
	imshow("origin", src);
	imshow("result", dst);
	waitKey(0);
	return 0;
}
