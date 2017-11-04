#pragma once
#include<cmath>
class Distance
{
public:
	Distance(float x1 = 0,float y1 = 0, float x2 = 0, float y2 = 0);
	float distance();
	~Distance();
private:
	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;

};

