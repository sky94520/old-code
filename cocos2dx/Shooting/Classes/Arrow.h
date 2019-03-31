#ifndef __Arrow_H__
#define __Arrow_H__
#include "Entity.h"
class Arrow:public Entity
{
protected:
	bool m_bAlive;//�ü��Ƿ���

	CC_SYNTHESIZE(int,m_nDamage,Damage);//�˺�ֵ
public:
	Arrow();
	~Arrow();
	virtual void start(const Point&from,const Point&to)=0;//��ʼʱ����
	virtual void dead()=0;//����ʱ����
	virtual void end()=0;//����ǽ��ʱ����
	bool isAlive()const;
};
#endif