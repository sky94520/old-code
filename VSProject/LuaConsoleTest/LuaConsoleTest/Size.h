#ifndef __Size_H__
#define __Size_H__
#include<assert.h>
#include<cmath>
#include "SEMath.h"
#include "Point.h"
class Size
{
public:
	int width;
	int height;
	
	static const Size ZERO;
public:
	Size(int w=0,int h=0);
	~Size(){}
	//复制构造函数
	Size(const Size& s);
	Size&operator=(const Size &other);

	Size operator+(Size &size);
	Size operator-(Size &size);
	Size operator*(float a) const;
	Size operator/(float a) const;
	Size operator/(const Size&other)const;
	//重载==运算符
	bool operator==(const Size&other)const;
	bool operator!=(const Size&other)const;
	void setSize(float width,float height);
	bool equals(const Size &s) const;

	bool containsPoint(const Point&pos)const;
};
#endif