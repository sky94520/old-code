#ifndef __Player_H__
#define __Player_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"
using namespace SDL;

class Player:public Entity
{
	SDL_SYNTHESIZE(float,m_moveSpeed,MoveSpeed);//移动速度
private:
	float m_invulnerableTime;//复活后的无敌时间
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	bool init();
	//复活
	void ressurect(float invulnerableTime);
	//正常动画
	void runNormalAnimation();
	//主角是否无敌
	bool isInvulnerable()const;
	//设置旋转角度
	void setPlayerRotation(float angle);

	virtual void onBindSprite();
	virtual void onHurt(int damage);
	virtual void onDead();
};
#endif