#ifndef __Enemy_H__
#define __Enemy_H__
#include "Entity.h"
class Enemy:public Entity
{
private:
	int m_nDeadFrameNum;//死亡帧数目

	CC_SYNTHESIZE(int,m_nID,ID);//id
	CC_SYNTHESIZE(std::string,m_name,Name);//name
	CC_SYNTHESIZE(float,m_speed,Speed);//speed
	CC_SYNTHESIZE(int,m_nScore,Score);//分数
	CC_SYNTHESIZE(float,m_elapased,Elapased);//消逝时间
	CC_SYNTHESIZE(float,m_time,Time);//在多少秒后会出现
public:
	Enemy();
	static Enemy*createWithID(int id);
	bool initWithID(int id);
	virtual void update(float dt);
	virtual void onHurt();
	virtual void onDead();
};
#endif