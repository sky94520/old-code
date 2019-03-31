#ifndef __Player_H__
#define __Player_H__
#include<cstdio>
typedef struct Point
{
	int x;
	int y;
	Point(int x=0,int y=0):x(x),y(y){}
}Point;
class Player
{
private:
	Point position;
	char sprite;//��ͼ֡
public:
	Player();
	~Player();

	void bindSprite(char sprite);

	void setPosition(int x,int y);//����λ��
	void setPosition(const Point&pos);

	Point getPosition()const;
	void render();//��Ⱦ
};
#endif