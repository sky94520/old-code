#ifndef __PoleVaultingZombie_H__
#define __PoleVaultingZombie_H__
#include<string>
#include "ZombieBase.h"
using namespace std;

class Plant;

class PoleVaultingZombie : public ZombieBase
{
private:
	enum class State
	{
		None,
		Walk,
		Attack,
		WalkDead,
		AttackDead,
		Jump,
		Jump2,
	};
private:
	bool m_bLosePole;//是否失去了撑杆
	bool m_bIsActiveForBullet;//是否对子弹有效
	State m_state;
	State m_oldState;
	float m_duration;
	float m_elapsed;
public:
	PoleVaultingZombie();
	~PoleVaultingZombie();

	static PoleVaultingZombie*create(const string&zombieName);
	bool init(const string&zombieName);
protected:
	virtual void updateAlive(float dt);
	virtual bool isCanMove()const;
	virtual float getCurSpeed()const;
	virtual Rect getCollisionBoundingBox()const;
	virtual void onNormalDead();
	virtual void onCRPDead();
	virtual bool isActiveForBullet()const;
	virtual void onButterDebuffEnter(const Point&pos);
	virtual void onButterDebuffExit();
	virtual void onIceDebuffExit();
private:
	void jump();//僵尸跳起
	void jump2();//跳起阶段2
	void jumpEnd();
	void changeState(State state);
	void showZombieHead();
};
#endif