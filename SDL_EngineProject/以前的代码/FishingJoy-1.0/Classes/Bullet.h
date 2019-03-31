#ifndef __Bullet_H__
#define __Bullet_H__
#include "Cannon.h"
#include "Entity.h"
class Fish;
class BulletDelegate
{
public:
	virtual ~BulletDelegate(){}
	virtual CannonType getCannonType()const=0;
	virtual void showAt(const Point&pos)=0;
};
class Bullet:public Entity
{
private:
	BulletDelegate*m_pDelegate;
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	bool init();
public:
	void setDelegate(BulletDelegate*pDelegate);
public:
	Rect getBulletCollisionRect()const;
	
	void flyTo(const Point&target,float angle=0.f);
	void end();
};
#endif