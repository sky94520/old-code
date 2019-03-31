#ifndef __Pea_H__
#define __Pea_H__
#include<string>
#include "Plant.h"
class ZombieBase;
using namespace std;
/*豌豆植物的父类，所有的豌豆类植物必须继承于此*/
class Pea : public Plant
{
protected:
	enum class State
	{
		Normal,
		Attack,
		AttackEnd,
	};
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//伤害值
	SDL_SYNTHESIZE(int,m_nBulletNumber,BulletNumber);
private:
	float _elapsed;
protected:
	State m_state;
public:
	Pea();
	~Pea();
protected:
	virtual void updateHook(float dt);
	/*查找第一个僵尸,默认查找所在行的僵尸*/
	virtual ZombieBase* findFirstZombie();
	/*改变状态*/
	virtual void changeState(State state);
	virtual void updateAttackState(float dt) = 0;
	virtual void updateAttackEndState(float dt) = 0;
private:
	void updateNormal(float dt);
protected:
	void shootPeaBullet(int row,bool bRight = true);
	void shootPeaBullet(int row,const Point&pos,bool bRight = true);

	void shootSnowPea(int row);
	void shootFirePeaBullet(int row);
};
#endif