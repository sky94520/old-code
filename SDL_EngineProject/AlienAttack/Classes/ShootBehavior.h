#ifndef __ShootBehavior_H__
#define __ShootBehavior_H__

class Enemy;
class EnemyLayerDelegate;

class ShootBehavior
{
public:
	virtual ~ShootBehavior(){}
	virtual void shoot(Enemy*enemy)=0;
};
//-----------------------µ¥¸ö¾¶Ö± SingleShooter------------------------------------------------------
class SingleShooter:public ShootBehavior
{
private:
	EnemyLayerDelegate*m_pDelegate;
public:
	SingleShooter(EnemyLayerDelegate*pDelegate);
	virtual void shoot(Enemy*enemy);
};
//----------------------EsketletorShooter------------------------------------
class EsketletorShooter:public ShootBehavior
{
private:
	EnemyLayerDelegate*m_pDelegate;
public:
	EsketletorShooter(EnemyLayerDelegate*pDelegate);
	virtual void shoot(Enemy*enemy);
};
//---------------------TurretShooter------------------------------------------
class TurretShooter:public ShootBehavior
{
private:
	EnemyLayerDelegate*m_pDelegate;
public:
	TurretShooter(EnemyLayerDelegate*pDelegate);
	virtual void shoot(Enemy*enemy);
};
//---------------------RoofTurretShooter-------------------------------------
class RoofTurretShooter:public ShootBehavior
{
private:
	EnemyLayerDelegate*m_pDelegate;
public:
	RoofTurretShooter(EnemyLayerDelegate*pDelegate);
	virtual void shoot(Enemy*enemy);
};
#endif