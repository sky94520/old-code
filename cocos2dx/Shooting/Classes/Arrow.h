#ifndef __Arrow_H__
#define __Arrow_H__
#include "Entity.h"
class Arrow:public Entity
{
protected:
	bool m_bAlive;//该箭是否存活

	CC_SYNTHESIZE(int,m_nDamage,Damage);//伤害值
public:
	Arrow();
	~Arrow();
	virtual void start(const Point&from,const Point&to)=0;//开始时调用
	virtual void dead()=0;//死亡时调用
	virtual void end()=0;//碰到墙体时调用
	bool isAlive()const;
};
#endif