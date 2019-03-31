#ifndef __IceShroom_H__
#define __IceShroom_H__

#include "NightPlant.h"

class IceShroom : public NightPlant
{
	SDL_SYNTHESIZE(int,m_nDamage,Damage);
private:
	enum class State
	{
		None,
		Normal,
		Sleeping,
	};
private:
	State m_state;
	float m_elapsed;
public:
	IceShroom();
	~IceShroom();
	static IceShroom*create(const string&plantName);
	bool init(const string&plantName);

	virtual void updateNotSleeping(float dt);
	virtual void onHurt();
	virtual void onSleepingEnter();
	virtual void onSleepingExit();
private:
	void changeState(State state);
	void skill();
};
#endif