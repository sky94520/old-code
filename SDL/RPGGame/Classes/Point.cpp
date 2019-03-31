#include "Point.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}
int Point::getPositionX()
{
	return this->x;
}
void Point::setPositionX(int i)
{
	this->x = i;
}
int Point::getPositionY()
{
	return this->y;
}
void Point::setPositionY(int i)
{
	this->y = i;
}

Point Point::getPosition()
{
  return Point(x,y);
}
void Point::setPosition(Point point)
{
    this->x = point.x;
    this->y = point.y;
}
void Point::setPosition(int a,int b)
{
    this->x = a;
    this->y = b;
}
