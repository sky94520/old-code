#ifndef __FlyBehavior_H__
#define __FlyBehavior_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Enemy;
class EnemyLayerDelegate;

class FlyBehavior
{
public:
	virtual ~FlyBehavior(){}
	virtual void fly(Enemy*enemy)=0;
};
//---------------FlyStraightlyֱ��----------------------------------
class FlyStraightly:public FlyBehavior
{
public:
	virtual void fly(Enemy*enemy);
};
//---------------FlyCrookedly ��������-------------------------------
class FlyCrookedly:public FlyBehavior
{
private:
	Point m_startPos;
	Point m_velocity;
	bool m_bFirst;
public:
	FlyCrookedly();
	virtual void fly(Enemy*enemy);
};
//---------------FlyDown���·���-------------------------------------
class FlyDown:public FlyBehavior
{
private:
	EnemyLayerDelegate*m_pDelegate;
public:
	FlyDown(EnemyLayerDelegate*pDelegate);
	virtual void fly(Enemy*enemy);
};
//-------------------------�����ͼ����---------------------------------
class FlyWithMap:public FlyBehavior
{
private:
	EnemyLayerDelegate*m_pDelegate;
public:
	FlyWithMap(EnemyLayerDelegate*pDelegate);
	virtual void fly(Enemy*enemy);
};
//----------------------------Boss1Fly----------------------------------
class Boss1Fly:public FlyBehavior
{
private:
	Point m_startPos;
	Point m_velocity;
	bool m_bFirst;
public:
	Boss1Fly();
	virtual void fly(Enemy*enemy);
};
#endif