#include "Point.h"
const Point Point::ZERO=Point(0.0f,0.0f);

Point::Point(const Point &point):x(point.x),y(point.y)
{
}
float Point::getX()
{
	return x;
}
void Point::setX(int x)
{
	this->x = x;
}
float Point::getY()
{
	return y;
}
void Point::setY(int y)
{
	this->y = y;
}
bool Point::equals(const Point &point) const
{
	return this->x == point.x
		&& this->y == point.y;
}