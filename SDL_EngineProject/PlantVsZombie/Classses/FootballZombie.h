#ifndef __FootballZombie_H__
#define __FootballZombie_H__

#include "Zombie.h"

class FootballZombie : public Zombie
{
public:
	FootballZombie();
	~FootballZombie();

	static FootballZombie*create(const string& zombieName);
	bool init(const string& zombieName);
protected:
	virtual void changeState(State state);
	virtual void onGarnishryDead();
	virtual void showZombieHead();
	virtual void onCRPDead();
	virtual void onButterDebuffEnter(const Point&pos);
	virtual void onButterDebuffExit();
};
#endif