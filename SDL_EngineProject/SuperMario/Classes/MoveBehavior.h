#ifndef __MoveBehavior_H__
#define __MoveBehavior_H__
#include "SDL_Engine/SDL_Engine.h"
#include "BehaviorManager.h"

using namespace SDL;

class BehaviorDelegate;
class BehaviorEntity;
class MoveBehavior
{
protected:
	BehaviorDelegate*m_pDelegate;
public:
	MoveBehavior();
	virtual ~MoveBehavior(){}
	virtual void performMove(BehaviorEntity*entity,float dt)=0;
	void setDelegate(BehaviorDelegate*pDelegate);
protected:
	void move(BehaviorEntity*entity,float dt,const Point &gravity);
};
//------------------------MoveNoWayBehavior-----------------------------------
class MoveNoWayBehavior:public MoveBehavior
{
public:
	virtual void performMove(BehaviorEntity*entity,float dt);
};
//------------------------MoveWithTileCollidedAndCanDrop----------------------
class MoveWithTileCollidedAndCanDrop:public MoveBehavior
{
public:
	virtual void performMove(BehaviorEntity*entity,float dt);
};
//------------------------MoveWithoutGravity--------------------------------
class MoveWithoutGravity:public MoveBehavior
{
public:
	virtual void performMove(BehaviorEntity*entity,float dt);
};
//------------------------MoveOnlyWithVelocity-------------------------------
class MoveOnlyWithVelocity:public MoveBehavior
{
public:
	virtual void performMove(BehaviorEntity*entity,float dt);
};
#endif