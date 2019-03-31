#ifndef __Bullet_H__
#define __Bullet_H__
#include "Entity.h"
class Bullet:public Entity
{
	CC_SYNTHESIZE(int,m_nSpeed,Speed);
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	bool init();
	virtual void onHurt();
	virtual void onDead();
};
#endif