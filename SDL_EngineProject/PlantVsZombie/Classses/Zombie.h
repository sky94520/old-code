#ifndef __Zombie_H__
#define __Zombie_H__
#include<string>
#include "ZombieBase.h"
using namespace std;

class Zombie : public ZombieBase
{
protected:
	enum class State
	{
		None,
		Idle,
		Walk,
		Attack,
		Dead,
		WalkDead,
		AttackDead,
	};
protected:
	State m_state;
	State m_oldState;
private:
	int m_nType;
public:
	Zombie();
	~Zombie();
	static Zombie*create(const string&zombieName);
	bool init(const string&zombieName);

	virtual void updateAlive(float dt);
	virtual bool isCanMove()const;

	virtual void onNormalDead();
protected:
	virtual void changeState(State state);
	virtual void showZombieHead();
	virtual void onButterDebuffEnter(const Point&pos);
	virtual void onButterDebuffExit();
	virtual void onIceDebuffExit();
};
#endif