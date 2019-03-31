#ifndef __Enemy_H__
#define __Enemy_H__
#include "Entity.h"
#include "BulletLayer.h"

class FlyBehavior;
class ShootBehavior;

enum EnemyType
{
	kEnemyType_None,
	kEnemyType_Glider,//滑翔机
	kEnemyType_ShotGlider,//会发射子弹的滑翔机
	kEnemyType_Turret,//
	kEnemyType_RoofTurret,
	kEnemyType_Eskeletor,
	kEnemyType_Level1Boss
};
class Enemy:public Entity
{
	SDL_SYNTHESIZE(EnemyType,m_type,Type);//敌机类型
	SDL_SYNTHESIZE(BulletType,m_bulletType,BulletType);//子弹类型
	SDL_SYNTHESIZE(float,m_speed,Speed);//速度
	SDL_SYNTHESIZE(int,m_worth,Worth);//价值
	SDL_BOOL_SYNTHESIZE(m_bUpdate,Update);//是否应该更新
	SDL_SYNTHESIZE(float,m_elpased,Elpased);//流逝值
	SDL_SYNTHESIZE(float,m_shootInterval,ShootInterval);//每隔多少秒射击
	SDL_SYNTHESIZE_RETAIN(Animate*,m_pDeadAction,DeadAction);//死亡动画
private:
	FlyBehavior*m_pFlyBehavior;//飞行行为
	ShootBehavior*m_pShootBehavior;//射击行为
public:
	Enemy();
	~Enemy();
	CREATE_FUNC(Enemy);
	bool init();
	virtual void update(float dt);
	
	virtual void onDead();

	void setFlyBehavior(FlyBehavior*behavior);
	void setShootBehavior(ShootBehavior*behavior);
	void reset();
};
#endif