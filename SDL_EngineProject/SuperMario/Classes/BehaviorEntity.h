#ifndef __BehaviorEntity_H__
#define __BehaviorEntity_H__
#include "Entity.h"

class MoveBehavior;

class BehaviorEntity:public Entity
{
protected:
	MoveBehavior*m_pMoveBehavior;//移动行为
public:
	BehaviorEntity();
	~BehaviorEntity();

	virtual void performMove(float dt);
	void setMoveBehavior(MoveBehavior*moveBehavior);
	MoveBehavior*getMoveBehavior();
	//hook函数，在MoveBehavior中可能会调用
	virtual bool tileCollidedX(bool bRight)=0;
	virtual bool tileCollidedY(bool bDown)=0;
};
#endif