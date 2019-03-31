#ifndef __ConeheadZombie_H__
#define __ConeheadZombie_H__
#include<string>
#include "Zombie.h"
using namespace std;
/*由于资源和帧动画限制，只能继承自Zombie*/
class ConeheadZombie : public Zombie
{
	SDL_SYNTHESIZE(string,m_nextZombieName,NextZombieName);
protected:
	bool m_bGarnishryDead;//饰品是否死亡
public:
	ConeheadZombie();
	~ConeheadZombie();
	static ConeheadZombie*create(const string&zombieName);
	bool init(const string&zombieName);
	virtual void setSpriteFlipX(bool flipX);
protected:
	virtual void onGarnishryDead();
	virtual void changeState(State state);
	virtual void showZombieHead();
	virtual void judgeInnerSpritePos();
	virtual void onButterDebuffEnter(const Point&pos);
	virtual void onButterDebuffExit();
};
#endif