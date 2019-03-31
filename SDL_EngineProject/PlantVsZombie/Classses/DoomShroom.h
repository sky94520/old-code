#ifndef __DoomShroom_H__
#define __DoomShroom_H__

#include "NightPlant.h"
class DoomShroom : public NightPlant
{
	SDL_SYNTHESIZE(int,m_nDamage,Damage);
private:
	enum class State
	{
		Normal,
		Sleeping,
		Boom,
	};
private:
	State m_state;
	float m_elapsed;
	float m_boomDuration;
public:
	DoomShroom();
	~DoomShroom();
	static DoomShroom*create(const string&plantName);
	bool init(const string& plantName);
protected:
	//不睡觉更新函数
	virtual void updateNotSleeping(float dt);
	virtual void onSleepingEnter();
	virtual void onSleepingExit();
	virtual void onHurt();
private:
	void changeState(State state);
	void boom();
};
#endif