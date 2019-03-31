#ifndef __ScreenDoorZombie_H__
#define __ScreenDoorZombie_H__

#include "ConeheadZombie.h"

class ScreenDoorZombie : public ConeheadZombie
{
public:
	ScreenDoorZombie();
	~ScreenDoorZombie();
	static ScreenDoorZombie* create(const string& zombieName);
	bool init(const string& zombieName);
protected:
	virtual void onGarnishryDead();
	virtual void changeState(State state);
	virtual void judgeInnerSpritePos();
};
#endif