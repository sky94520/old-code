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
	SDL_SYNTHESIZE(int,m_nCurHp,CurHp);//��ǰhp
	SDL_SYNTHESIZE(int,m_nMaxHp,MaxHp);//���hp
	//SDL_SYNTHESIZE(float,m_curAngle,CurAngle);//��ǰ�Ƕ�
	SDL_SYNTHESIZE(float,m_curSpeed,CurSpeed);//��ǰ�ٶ�
	SDL_SYNTHESIZE(int,m_nAtk,Atk);//������
protected:
	Sprite*m_pSprite;
	FlyBehavior*m_pFlyBehavior;
public:
	Entity();
	~Entity();
	void bindSprite(Sprite*sprite);
	Sprite*getSprite()const;
	//��������[begin,end]��ʱ������ʹ��AnimationCache����createAnimate
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
public:
	void hurt(int damage);
	bool isDead()const;
	//hook
	virtual void onBindSprite();
	virtual void onHurt(int damage);
	virtual void onDead();

	void setFlyBehavior(FlyBehavior*behavior);
	//���÷�����Ϊ������������
	virtual void update(float dt);
};
#endif