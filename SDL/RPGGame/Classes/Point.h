#ifndef __Point_H__
#define __Point_H__
class Point
{
private:
	int x;
	int y;
public:
	Point();
	Point(int a,int b) : x(a),y(b){}
	~Point(){}
	Point(const Point&v);

	int getPositionX();
	void setPositionX(int i);
	int getPositionY();
	void setPositionY(int i);

	Point getPosition();
	void setPosition(Point point);
	void setPosition(int a,int b);
};
#endif // __Point_H__
