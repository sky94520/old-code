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
	bool m_bLosePole;//�Ƿ�ʧȥ�˳Ÿ�
	bool m_bIsActiveForBullet;//�Ƿ���ӵ���Ч
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
	void jump();//��ʬ����
	void jump2();//����׶�2
	void jumpEnd();
	void changeState(State state);
	void showZombieHead();
};
#endif