#ifndef __Plane_H__
#define __Plane_H__
#include "Entity.h"
#include "BulletFactory.h"
class Plane;

class PlaneDelegate
{
public:
	virtual ~PlaneDelegate(){}
	virtual void shooting(Plane*plane,BulletType type)=0;
};
class Plane:public Entity
{
	SDL_SYNTHESIZE(b2Filter,m_bulletFilter,BulletFilter);//子弹碰撞属性
	SDL_SYNTHESIZE(int,m_nBulletNum,BulletNum);//一次能发射子弹的最大数目
private:
	PlaneDelegate*m_pDelegate;
public:
	Plane();
	~Plane();
	CREATE_FUNC(Plane);
	bool init();
	//发射子弹
	bool shoot();
	virtual void update(float dt);
	virtual void onDead();
	PlaneDelegate*getDelegate()const;
	void setDelegate(PlaneDelegate*pDelegate);
};
#endif