#ifndef __ScaredyShroom_H__
#define __ScaredyShroom_H__
#include "NightPlant.h"
class ZombieBase;

class ScaredyShroom : public NightPlant
{
	SDL_SYNTHESIZE(int,m_nDamage,Damage);
private:
	enum class State
	{
		Normal,
		Attack,
		Sleeping,
		Scared,
	};
private:
	State m_state;
	float m_elapsed;
public:
	ScaredyShroom();
	static ScaredyShroom*create(const string& plantName);
	bool init(const string& plantName);
protected:
	virtual void updateNotSleeping(float dt);
	virtual void onSleepingEnter();
	virtual void onSleepingExit();

	virtual void updateAtkState(float dt);
	virtual void changeState(State state);
private:
	void updateNormalState(float dt);
	void updateScaredState(float dt);
	void findZombie(ZombieBase*zombie);
	bool isScared(ZombieBase*zombie);
};
#endif