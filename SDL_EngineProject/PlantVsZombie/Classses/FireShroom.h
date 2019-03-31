#ifndef __FireShroom_H__
#define __FireShroom_H__

#include "NightPlant.h"
class ZombieBase;

class FireShroom : public NightPlant
{
public:
	FireShroom();
	~FireShroom();
	SDL_SYNTHESIZE(float,m_attackScope,AttackScope);//¹¥»÷·¶Î§
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//¹¥»÷Á¦
protected:
	enum class State
	{
		Normal,
		Attack,
		Sleeping,
	};
protected:
	State m_state;
private:
	float _elapsed;
protected:
	virtual void updateNotSleeping(float dt);
	virtual void onSleepingEnter();
	virtual void onSleepingExit();

	virtual void changeState(State state) = 0;
	virtual void updateAtkState(float dt) = 0;
private:
	void updateNormalState(float dt);
};
#endif