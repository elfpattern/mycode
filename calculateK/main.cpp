#include<iostream>
#include<math.h>
using namespace std;
float calculatek(float x1, float y1,float x2, float y2);
float calculateb(float x3, float y3, float K);
void simplex(float K, float B, float x3, float y3);
int main()
{
	float x1,y1;
	float x2, y2;
	float x3, y3;
	cout << "please input x1,y1,x2,y2,x3,y3:";
	cin >> x1;
	cin >> y1;
	cin >> x2;
	cin >> y2;
	cin >> x3;
	cin >> y3;
	float K = calculatek(x1,y1,x2,y2);
	float B = calculateb(x3, y3, K);
	simplex(K, B, x3, y3);
	
	cout << "K:" << K << endl;
	cout << "B:" << B << endl;
	system("pause");
	return 0;
}
float calculatek(float x1, float y1, float x2, float y2)
{
	float temp1 = y2 - y1;
	float temp2 = x2 - x1;
	float k = -temp2 / temp1;
	return k;
}
float calculateb(float x3, float y3, float K)
{
	float temp = K * x3;
	float b = y3 - temp;
	return b;
}
void simplex(float K, float B, float x3, float y3)
{
	int r = 5;
	float parA = 1 + K * K;
	float temp1 = K * (B - y3);
	float parB = 2 * (temp1 - x3);
	float temp2 = (B - y3) * (B - y3);
	float parC = x3 * x3 + temp2 - r * r;
	float delta = parB * parB - 4 * parA * parC;
	if (delta >= 0)
	{
		float x1 = -(parB + sqrt(delta)) / (2 * parA);
		float y1 = K * x1 + B;
		float x2 = -(parB - sqrt(delta)) / (2 * parA);
		float y2 = K * x2 + B;
		cout << "the x1,y1:" << "(" << x1 << "," << y1 << ")" << endl;
		cout << "the x2,y2:" << "(" << x2 << "," << y2 << ")" << endl;
	}
	else
		cout << "the x is not a good value" << endl;
}