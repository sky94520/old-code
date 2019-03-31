#ifndef __Enemy_H__
#define __Enemy_H__
#include "Entity.h"
class Enemy:public Entity
{
private:
	int m_nDeadFrameNum;//����֡��Ŀ

	CC_SYNTHESIZE(int,m_nID,ID);//id
	CC_SYNTHESIZE(std::string,m_name,Name);//name
	CC_SYNTHESIZE(float,m_speed,Speed);//speed
	CC_SYNTHESIZE(int,m_nScore,Score);//����
	CC_SYNTHESIZE(float,m_elapased,Elapased);//����ʱ��
	CC_SYNTHESIZE(float,m_time,Time);//�ڶ����������
public:
	Enemy();
	static Enemy*createWithID(int id);
	bool initWithID(int id);
	virtual void update(float dt);
	virtual void onHurt();
	virtual void onDead();
};
#endif