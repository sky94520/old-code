#ifndef __DoubleBulletItem_H__
#define __DoubleBulletItem_H__
#include "Entity.h"
#include "SystemHeader.h"
class DoubleBulletItem:public Entity
{
	CC_SYNTHESIZE_READONLY(float,m_intervalTime,IntervalTime);//道具出现间隔
	CC_SYNTHESIZE_READONLY(float,m_duration,Duration);//道具效果持续时间
	CC_SYNTHESIZE_READONLY(float,m_speed,Speed);//道具移动速度
	CC_SYNTHESIZE(float,m_elapsed,Elapsed);//流逝时间
	MY_SYNTHESIZE_BOOL(m_bInvalid,Invalid);//道具是否失效
public:
	DoubleBulletItem();
	~DoubleBulletItem();
	CREATE_FUNC(DoubleBulletItem);
	bool init();

	virtual void onHurt();
	virtual void onDead();
};
#endif