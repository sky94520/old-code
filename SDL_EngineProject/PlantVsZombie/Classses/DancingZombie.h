#ifndef __DancingZombie_H__
#define __DancingZombie_H__

#include "ZombieBase.h"

class BackupDancer;

class DancingZombie : public ZombieBase
{
private:
	enum class State
	{
		None,
		SlidingStep,
		Walk,
		Dancing,
		Summon,
		Attack,
		Dying,
	};
private:
	State m_state;
	bool m_bDying;
	bool m_bDirty;
	float m_elapsed;
	float m_duration;
	BackupDancer* m_innerZombies[4];
public:
	DancingZombie();
	~DancingZombie();
	static DancingZombie* create(const string& zombieName);
	bool init(const string& zombieName);

	virtual void updateAlive(float dt);
	virtual bool isCanMove()const;
private:
	virtual void onNormalDead();
	void changeState(State state);
	void showZombieHead();

	void updateWalkState(float dt);
	void summon(float );
	//ÄÚ²¿½©Ê¬ÊÇ·ñËÀÍö
	bool isDeadForInnerZombie();
};
#endif