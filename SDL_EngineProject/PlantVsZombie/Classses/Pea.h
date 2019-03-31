#ifndef __Pea_H__
#define __Pea_H__
#include<string>
#include "Plant.h"
class ZombieBase;
using namespace std;
/*�㶹ֲ��ĸ��࣬���е��㶹��ֲ�����̳��ڴ�*/
class Pea : public Plant
{
protected:
	enum class State
	{
		Normal,
		Attack,
		AttackEnd,
	};
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//�˺�ֵ
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
	/*���ҵ�һ����ʬ,Ĭ�ϲ��������еĽ�ʬ*/
	virtual ZombieBase* findFirstZombie();
	/*�ı�״̬*/
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