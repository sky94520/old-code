#ifndef __DoubleBulletItem_H__
#define __DoubleBulletItem_H__
#include "Entity.h"
#include "SystemHeader.h"
class DoubleBulletItem:public Entity
{
	CC_SYNTHESIZE_READONLY(float,m_intervalTime,IntervalTime);//���߳��ּ��
	CC_SYNTHESIZE_READONLY(float,m_duration,Duration);//����Ч������ʱ��
	CC_SYNTHESIZE_READONLY(float,m_speed,Speed);//�����ƶ��ٶ�
	CC_SYNTHESIZE(float,m_elapsed,Elapsed);//����ʱ��
	MY_SYNTHESIZE_BOOL(m_bInvalid,Invalid);//�����Ƿ�ʧЧ
public:
	DoubleBulletItem();
	~DoubleBulletItem();
	CREATE_FUNC(DoubleBulletItem);
	bool init();

	virtual void onHurt();
	virtual void onDead();
};
#endif