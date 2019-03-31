#ifndef __BackupDancer_H__
#define __BackupDancer_H__
#include "ZombieBase.h"

class BackupDancer : public ZombieBase
{
private:
	enum class State
	{
		None,
		Rising,
		Walk,
		Attack,
		Dance,
		WalkDead,
		AttackDead,
		DanceDead,
	};
private:
	State m_state;
	float m_duration;
	float m_elapsed;
public:
	BackupDancer();
	~BackupDancer();
	static BackupDancer*create(const string& zombieName);
	bool init(const string& plantName);

	virtual void updateAlive(float dt);
	virtual bool isCanMove()const;
private:
	virtual void onNormalDead();
	void changeState(State state);
	void showZombieHead();
	void updateWalkState(float dt);
};
#endif