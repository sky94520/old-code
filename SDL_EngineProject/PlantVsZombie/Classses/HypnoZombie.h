#ifndef __HypnoZombie_H__
#define __HypnoZombie_H__
#include "Plant.h"

class ZombieBase;
class HypnoZombie : public Plant
{
private:
	ZombieBase*m_pInnerZombie;
public:
	HypnoZombie();
	~HypnoZombie();
	static HypnoZombie* create(ZombieBase* zombie);
	bool init(ZombieBase* zombie);
	virtual Rect getCollisionBoundingBox()const;
protected:
	//每次更新都会调用的钩子函数
	virtual void updateHook(float dt);
};
#endif