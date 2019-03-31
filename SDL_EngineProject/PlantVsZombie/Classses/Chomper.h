#ifndef __Chomper_H__
#define __Chomper_H__
#include "Plant.h"

class ZombieBase;

class Chomper : public Plant
{
	SDL_SYNTHESIZE(float,m_scope,Scope);//������Χ
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//�˺�ֵ
private:
	enum class State
	{
		Normal,
		AttackStart,
		AttackEnd,
		Digesting,
		Success,
	};
private:
	State m_state;
	float m_elapsed;
	float m_duration;
	//Ŀ�꽩ʬ
	ZombieBase*m_pAimZombie;
public:
	Chomper();
	~Chomper();
	static Chomper*create(const string&plantName);
	bool init(const string&plantName);

	virtual void updateHook(float dt);
private:
	void updateNormalState(float dt);
	void changeState(State state);
};
#endif