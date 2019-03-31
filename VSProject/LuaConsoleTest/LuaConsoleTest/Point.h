#ifndef __Point_H__
#define __Point_H__
#include<cmath>
#include "SEMath.h"
class Point
{
public:
	int x;
	int y;
public:
	static const Point ZERO;
  public:
	Point(int x = 0.f, int y = 0.f):x(x), y(y){}
	Point(const Point&point);
	~Point(){}

	float getX();
	void setX(int x);
	float getY();
	void setY(int y);
	float length()
	{
		return sqrt(x * x + y * y);
	}
	void normalize()
	{
		float l = length();
		if (l > 0)
		{
			(*this) *= 1/l;
		}
	}
	/*ÖØÔØ*/
	//+
	Point operator+(const Point &v2) const
	{
		return Point(x + v2.x,y + v2.y);
	}
	//*
	Point operator*(float scalar)
	{
		return Point(x * scalar,y * scalar);
	}
	//*=
	Point& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}
	//-
	Point operator-(const Point& v2) const
	{
		return Point(x - v2.x,y - v2.y);
	}
	// /¡Â
	Point operator/(float scalar)
	{
		return Point(x /scalar,y/scalar);
	}
	//  /=
	Point& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}
	/*ÓÑÔª*/
	//+=
	friend Point& operator+=(Point &v1,const Point &v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;

		return v1;
	}
	//-=
	friend Point& operator-=(Point& v1,const Point& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;

		return v1;
	}
	friend bool operator!=(const Point&p1,const Point&p2)
	{
		return !p1.equals(p2);
	}
	friend bool operator==(const Point&p1,const Point&p2)
	{
		return p1.equals(p2);
	}
	bool equals(const Point &point) const;
};
#endif