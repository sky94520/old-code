#ifndef __CannonLayer_H__
#define __CannonLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Weapon;
class Fish;
class CannonLayer:public Layer
{
private:
	Weapon*m_pWeapon;
	Sprite*m_pBackground;
public:
	CannonLayer();
	~CannonLayer();
	CREATE_FUNC(CannonLayer);
	bool init();
public:
	void aimAt(const Point&target);
	void shootTo(const Point&target);

	Weapon*getWeapon()const;
private:
	void addWeaponLevel(Object*);
	void subWeaponLevel(Object*);
};
#endif