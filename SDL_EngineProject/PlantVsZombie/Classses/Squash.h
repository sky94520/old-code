#ifndef __Squash_H__
#define __Squash_H__
#include "Plant.h"

class ZombieBase;

class Squash : public Plant
{
	SDL_SYNTHESIZE(float,m_scope,Scope);//������Χ
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//�����˺�
private:
	enum class State
	{
		Normal,
		Left,
		LeftEnd,
		Right,
		RightEnd,
		Attack,
		AttackEnd,
	};
private:
	State m_state;
	float m_elapsed;
	float m_duration;
	ZombieBase*m_pAimZombie;
	static float s_jumpHeight;//��Ծ�߶�
public:
	Squash();
	~Squash();
	static Squash*create(const string&plantName);
	bool init(const string& plantName);
protected:
	virtual void updateHook(float dt);
private:
	void updateNormalState(float dt);
	void updateLeftOrRightState(float dt);
	void updateAttackState(float dt);
	void updateAttackEndState(float dt);

	void changeState(State state);
};
#endif