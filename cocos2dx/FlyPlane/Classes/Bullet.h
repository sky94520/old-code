#ifndef __Bullet_H__
#define __Bullet_H__
/*子弹类*/
#include "Entity.h"

class Bullet : public Entity
{
public:
	CREATE_FUNC(Bullet);
	virtual bool init();

	Bullet();
	~Bullet();

public:
	void show();
	void hide();
	//根据给出的坐标点决定以哪为起点
	void reset(Point point);
	int getSpeed();
	bool isAlive();
	
private:
	int m_speed;
	bool m_isAlive;

};
#endif