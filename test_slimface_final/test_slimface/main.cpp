#include<iostream>
#include"Warp.h"
#include"Distance.h"
using namespace std;


int main()
{
	Mat src = imread("C:/Users/jingzhao004214/Desktop/33888.jpg");
	int strength = 5; //通过改变strength的大小，控制瘦脸的程度，当strength为负的时候，是在大脸
	imshow("ori_image", src);
	//-----29215.jpg------------------------------------
	//Point NoseCenter = Point(208.8445, 184.3999);//34点
	//Point Left = Point(139.6033, 226.0516);//70点
	//Point Right = Point(274.7032, 227.8738);//78点
	//----------------------------------------------------

	//-------33888.jpg------------------------------
	Point NoseCenter = Point(419.603, 306.7044);//34点
	Point Left = Point(285.7143, 375.9152);//70点
	Point Right = Point(491.4286, 329.4866);//78点
	//-----------------------------------------------
	//计算半径
	Distance A(Left.x, Left.y, NoseCenter.x, NoseCenter.y);
	int LeftR = A.distance();

	Distance B(Right.x, Right.y, NoseCenter.x, NoseCenter.y);
	int RightR = B.distance();

	//左脸
	Point end1 = Point(Left.x + strength, Left.y);
	Warp left_face(LeftR);
	left_face.warping(src,Left, end1);
	imshow("change_leftface_image",src);

	//右脸
	Point end2 = Point(Right.x - strength, Right.y);
	Warp right_face(RightR);
	right_face.warping(src, Right, end2);
	imshow("change_rightface_image", src);
	waitKey(0);
	return 0;
}


