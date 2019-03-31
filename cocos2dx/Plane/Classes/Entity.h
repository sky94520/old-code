#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"
USING_NS_CC;
class Entity:public Node
{
	CC_SYNTHESIZE(int,m_nHitPoints,HitPoints);//HP
	CC_SYNTHESIZE(int,m_nCurHP,CurHP);//当前hp
	CC_SYNTHESIZE(int,m_nDamage,Damage);//伤害
	CC_SYNTHESIZE(int,m_nDefense,Defense);//防御
protected:
	Sprite*m_pSprite;
public:
	Entity();
	~Entity();
	Sprite*getSprite()const;
	void bindSprite(Sprite*sprite);
	//创建动画[begin,end]
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
public:
	bool isAlive()const;//是否存活
	void hurt(int damage);//受伤
	virtual void onHurt()=0;//受伤时调用
	void dead();//死亡
	virtual void onDead()=0;//死亡时调用
};
#endif