#include "Size.h"

const Size Size::ZERO = Size(0.f,0.f);
Size::Size(int w,int h)
:width(w),height(h)
{
}
Size::Size(const Size &s):width(s.width),height(s.height)
{
}
Size &Size::operator=(const Size&other)
{
	setSize(other.width,other.height);
	return *this;
}
Size Size::operator+(Size &size)
{
	return Size(width+size.width,height+size.height);
}
Size Size::operator-(Size &size)
{
	return Size(width-size.width,height-size.height);
}
Size Size::operator*(float a) const
{
	return Size(width*a,height*a);
}
Size Size::operator/(float a) const
{
	assert(a!=0,"CCSize division by 0.");
	return Size(width/a,height/a);
}
Size Size::operator/(const Size&other)const
{
	return Size(width/other.width,height/other.height);
}
bool Size::operator==(const Size&other)const
{
	return width == other.width&&
		height == other.height;
}
bool Size::operator!=(const Size&other)const
{
	return width != other.width ||
		height != other.height;
}
void Size::setSize(float width,float height)
{
	this->width = width;
	this->height = height;
}
bool Size::equals(const Size & s) const
{
	return this->width == s.width
		&& this->height == s.height;
}
bool Size::containsPoint(const Point&pos)const
{
	return pos.x >= 0 && pos.x < width
		&& pos.y >= 0 && pos.y < height;
}