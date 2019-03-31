#ifndef __Chomper_H__
#define __Chomper_H__
#include "Plant.h"

class ZombieBase;

class Chomper : public Plant
{
	SDL_SYNTHESIZE(float,m_scope,Scope);//¹¥»÷·¶Î§
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//ÉËº¦Öµ
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
	//Ä¿±ê½©Ê¬
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