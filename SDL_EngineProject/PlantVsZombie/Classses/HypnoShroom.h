#ifndef __HypnoShroom_H__
#define __HypnoShroom_H__
#include "NightPlant.h"

class ZombieBase;

class HypnoShroom : public NightPlant
{
private:
	enum class State
	{
		Normal,
		Sleeping,
	};
private:
	State m_state;
	ZombieBase*m_pAim;
public:
	HypnoShroom();
	~HypnoShroom();
	static HypnoShroom*create(const string& plantName);
	bool init(const string& plantName);

	virtual void eatenByZombie(ZombieBase*zombie);
protected:
	//不睡觉更新函数
	virtual void updateNotSleeping(float dt);
	virtual void onSleepingEnter();
	virtual void onSleepingExit();
private:
	void changeState(State state);
};
#endif