#ifndef __Threepeater_H__
#define __Threepeater_H__

#include "Pea.h"

class Threepeater : public Pea
{
public:
	Threepeater();
	~Threepeater();
	static Threepeater* create(const string& plantName);
	bool init(const string &plantName);
protected:
	virtual void updateAttackState(float dt);
	virtual void updateAttackEndState(float dt);
	virtual ZombieBase* findFirstZombie();
};
#endif