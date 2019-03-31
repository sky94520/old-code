#ifndef __ConeheadZombie_H__
#define __ConeheadZombie_H__
#include<string>
#include "ZombieBase.h"
using namespace std;
class ConeheadZombie : public ZombieBase
{
private:
	enum class State
	{
		Idle,
		Walk,
		Attack,
	};
private:
	ZombieBase*m_pInnerZombie;
	State m_state;
	float m_elapsed;
public:
	ConeheadZombie();
	~ConeheadZombie();

	static ConeheadZombie*create(const string&zombieName,ZombieBase*zombie);
	bool init(const string&zombieName,ZombieBase*zombie);

	virtual void setDelegate(ZombieDelegate*pDelegate);
	virtual void setAim(Terrain*plant);
	virtual void setMoveBehavior(MoveBehavior*behavior);

	virtual bool isDying()const;
	virtual bool isDead()const;
	virtual void update(float dt);
	virtual float getCurSpeed()const;
	virtual Rect getCollisionBoundingBox()const;
	//ÊÜÉË¹³×Óº¯Êý
	virtual int hurtHook(int baseDamage,AttackType attackType);
	virtual void onHurt();
	virtual void onDead();
private:
	void changeState(State state);
	void coneheadUpdate(float dt);
};
#endif