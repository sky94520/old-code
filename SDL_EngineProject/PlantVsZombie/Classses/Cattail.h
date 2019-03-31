#ifndef __Cattail_H__
#define __Cattail_H__
#include "VesselPlant.h"

class ZombieBase;

class Cattail : public VesselPlant
{
	SDL_SYNTHESIZE(int,m_nDamage,Damage);
private:
	enum class State
	{
		Normal,
		Attack,
		AttackEnd,
	};
private:
	State m_state;
	float m_elapsed;
	float m_duration;
	ZombieBase*m_pAim;
	int m_nBulletNum;
	int m_nCurBulletNum;
public:
	Cattail();
	~Cattail();
	static Cattail*create(const string& plantName);
	bool init(const string& plantName);
protected:
	virtual void updateHook(float dt);
private:
	void updateNormalState(float dt);
	void updateAtkState(float dt);
	void updateAtkEndState(float dt);

	void changeState(State state);
};
#endif