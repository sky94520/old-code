#ifndef __PaperZombie_H__
#define __PaperZombie_H__
#include<string>
#include "Zombie.h"

using namespace std;

class PaperZombie : public Zombie
{
private:
	bool m_bIsAngry;//读报僵尸是否生气
public:
	PaperZombie();
	~PaperZombie();
	static PaperZombie*create(const string&zombieName);
	bool init(const string&zombieName);

protected:
	virtual void changeState(State state);
	virtual void showZombieHead();
	virtual float getCurSpeed()const;
	virtual void onGarnishryDead();
	virtual void onCRPDead();
	virtual void onButterDebuffEnter(const Point&pos);
	virtual void onButterDebuffExit();
};
#endif