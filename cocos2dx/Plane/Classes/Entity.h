#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"
USING_NS_CC;
class Entity:public Node
{
	CC_SYNTHESIZE(int,m_nHitPoints,HitPoints);//HP
	CC_SYNTHESIZE(int,m_nCurHP,CurHP);//��ǰhp
	CC_SYNTHESIZE(int,m_nDamage,Damage);//�˺�
	CC_SYNTHESIZE(int,m_nDefense,Defense);//����
protected:
	Sprite*m_pSprite;
public:
	Entity();
	~Entity();
	Sprite*getSprite()const;
	void bindSprite(Sprite*sprite);
	//��������[begin,end]
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
public:
	bool isAlive()const;//�Ƿ���
	void hurt(int damage);//����
	virtual void onHurt()=0;//����ʱ����
	void dead();//����
	virtual void onDead()=0;//����ʱ����
};
#endif