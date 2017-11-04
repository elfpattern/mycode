#include "Distance.h"



Distance::Distance(float x1, float y1, float x2 , float y2):m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2)
{
}

float Distance::distance()
{
	float tempx = (m_x2 - m_x1) * (m_x2 - m_x1);
	float tempy = (m_y2 - m_y1) * (m_y2 - m_y1);
	float r = sqrt(tempx + tempy);
	return r;

}
Distance::~Distance()
{
}
