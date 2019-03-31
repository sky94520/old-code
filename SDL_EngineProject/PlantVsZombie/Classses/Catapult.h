#ifndef __Catapult_H__
#define __Catapult_H__
#include "Plant.h"
/*投手类植物*/
class Catapult : public Plant
{
	SDL_SYNTHESIZE(int,m_nDamage,Damage);
protected:
	enum class State
	{
		None,
		Normal,
		Attack,
		AttackEnd,
	};
protected:
	State m_state;
	float m_elapsed;
	float m_duration;
	ZombieBase*m_pAimZombie;
public:
	Catapult();
	~Catapult();

	virtual void updateHook(float dt);
protected:
	virtual void changeState(State state) = 0;
	virtual void shoot() = 0;
	virtual void shootEndHook() = 0;
};
#endif