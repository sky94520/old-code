#ifndef __Player_H__
#define __Player_H__
#include "Entity.h"
class Player:public Entity
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	bool init();
public:
	void reset();//÷ÿ÷√∑…ª˙£¨
	void onTouchMoved(Touch*touch,Event*event);
	virtual void onHurt();
	virtual void onDead();
};
#endif