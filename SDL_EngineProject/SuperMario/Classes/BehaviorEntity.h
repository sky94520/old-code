#ifndef __BehaviorEntity_H__
#define __BehaviorEntity_H__
#include "Entity.h"

class MoveBehavior;

class BehaviorEntity:public Entity
{
protected:
	MoveBehavior*m_pMoveBehavior;//�ƶ���Ϊ
public:
	BehaviorEntity();
	~BehaviorEntity();

	virtual void performMove(float dt);
	void setMoveBehavior(MoveBehavior*moveBehavior);
	MoveBehavior*getMoveBehavior();
	//hook��������MoveBehavior�п��ܻ����
	virtual bool tileCollidedX(bool bRight)=0;
	virtual bool tileCollidedY(bool bDown)=0;
};
#endif