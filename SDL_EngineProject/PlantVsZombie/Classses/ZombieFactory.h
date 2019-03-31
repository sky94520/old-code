#ifndef __ZombieFactory_H__
#define __ZombieFactory_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;

class ZombieBase;
class Zombie;
class ConeheadZombie;
class PaperZombie;
class PoleVaultingZombie;
class BucketheadZombie;

class ZombieFactory : public Object
{
public:
	ZombieFactory();
	~ZombieFactory();
	CREATE_FUNC(ZombieFactory);
	bool init();

	ZombieBase*makeZombie(const string& zombieName);
private:
	Point bindHpBarForZombie(ZombieBase*zombie);
	Point bindHpBarForZombie(ZombieBase*zombie,const Point&pos);
	void bindGarnihryForZombie(ZombieBase*zombie,const string&garnishryName);
};
#endif