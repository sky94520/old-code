#ifndef __Player_H__
#define __Player_H__
#include "Entity.h"
class Player:public Entity
{
private:
	Sprite*m_pPlayerArrow;//角色弓箭，可以移动的部分
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	bool init();
public:
	void aimAt(const Point&pos);
	void shootTo(const Point&pos);
};
#endif