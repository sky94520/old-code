#ifndef __FishingNet_H__
#define __FishingNet_H__
#include "Entity.h"
#include "Cannon.h"
class Fish;
class FishingNetDelegate
{
public:
	virtual ~FishingNetDelegate(){}
	virtual CannonType getCannonType()const=0;
};
class FishingNet:public Entity
{
private:
	FishingNetDelegate*m_pDelegate;
public:
	FishingNet();
	~FishingNet();
	CREATE_FUNC(FishingNet);
	bool init();
public:
	void setDelegate(FishingNetDelegate*pDelegate);
	void showAt(const Point&pos);

	Rect getFishingNetCollisionRect() const;
};
#endif