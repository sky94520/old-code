#ifndef __Entity_H__
#define __Entity_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class FlyBehavior;

class Entity:public Node
{
	SDL_BOOL_SYNTHESIZE(m_bAlive,Alive);
	SDL_SYNTHESIZE(int,m_nCurHp,CurHp);//当前hp
	SDL_SYNTHESIZE(int,m_nMaxHp,MaxHp);//最大hp
	//SDL_SYNTHESIZE(float,m_curAngle,CurAngle);//当前角度
	SDL_SYNTHESIZE(float,m_curSpeed,CurSpeed);//当前速度
	SDL_SYNTHESIZE(int,m_nAtk,Atk);//攻击力
protected:
	Sprite*m_pSprite;
	FlyBehavior*m_pFlyBehavior;
public:
	Entity();
	~Entity();
	void bindSprite(Sprite*sprite);
	Sprite*getSprite()const;
	//创建动画[begin,end]暂时这样，使用AnimationCache还是createAnimate
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
public:
	void hurt(int damage);
	bool isDead()const;
	//hook
	virtual void onBindSprite();
	virtual void onHurt(int damage);
	virtual void onDead();

	void setFlyBehavior(FlyBehavior*behavior);
	//调用飞行行为，子类必须调用
	virtual void update(float dt);
};
#endif