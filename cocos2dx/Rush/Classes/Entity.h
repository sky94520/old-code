#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"

USING_NS_CC;
class Entity : public Node
{
protected:
	Sprite*m_pSprite;
	bool m_bIsDead;//是否死亡
protected:
	virtual void onDead();//实体死亡时调用
	virtual void onBindSprite();//绑定精灵时调用
	virtual void onHurt(int nHurtValue);//受伤时调用
public:
	Entity();
	~Entity();
	CREATE_FUNC(Entity);
	virtual bool init();
	//获取精灵对象
	Sprite*getSprite();
	//帮顶精灵对象
	void bindSprite(Sprite*sprite);
	//被攻击
	void hurtMe(int nHurtValue);
	//是否死亡
	bool isDead();
	static Animation*createNormalAction(std::string format,int frameCountBegin,int frameCountEnd,int fps);

	CC_SYNTHESIZE(int,m_nID,ID);//实体ID
	CC_SYNTHESIZE(int,m_nModelID,ModelID);//资源ID
	CC_SYNTHESIZE(std::string,m_type,Type);//类别
	CC_SYNTHESIZE(std::string,m_name,Name);//名字
	CC_SYNTHESIZE(int,m_nHP,HP);
	CC_SYNTHESIZE(int,m_nDefense,Defense);//防御
	CC_SYNTHESIZE(float,m_nSpeed,Speed);//速度
	CC_SYNTHESIZE(int,m_nCurLevel,CurLevel);//等级
};
#endif