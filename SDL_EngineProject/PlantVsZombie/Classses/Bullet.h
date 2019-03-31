#ifndef __Bullet_H__
#define __Bullet_H__
#include <vector>
#include <functional>
#include "SDL_Engine/SDL_Engine.h"
#include "Character.h"

using namespace std;
using namespace SDL;

enum class BulletType
{
	Common,
	ShooterPeaBullet,
};
class ZombieBase;

class Bullet : public Character
{
public:
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//当前伤害
	SDL_SYNTHESIZE(AttackType,m_attackType,AttackType);//攻击类型
	SDL_SYNTHESIZE(float,m_duration,Duration);//debuff持续时间
	SDL_SYNTHESIZE(BulletType,m_bulletType,BulletType);//子弹类型
	SDL_BOOL_SYNTHESIZE(m_bCanTransform,CanTransform);//是否可以转换
	SDL_SYNTHESIZE(function<void ()>,m_stopRunningCallback,StopRunningCallback);//停止运行回调函数
	SDL_SYNTHESIZE(function<void ()>,m_deadCallback,DeadCallback);//死亡回调函数
protected:
	ZombieBase*m_pAimZombie;
	//保存已经攻击过的僵尸列表
	vector<ZombieBase*> m_attackedZombieList;
	int m_nRow;
public:
	Bullet();
	~Bullet();
	//设置目的僵尸
	void setAimZombie(ZombieBase*zombie);
	ZombieBase*getAimZombie();
	//添加怪物到已攻击列表中
	void addAttackedZombie(ZombieBase*zombie);
	//是否已经已经攻击过该僵尸了
	bool isHasAttacked(ZombieBase*zombie);
	void setRow(int row);
	//受伤函数
	void hurt();
	virtual int getRow()const;
	//碰撞结束后调用
	virtual void contactEnd();
	//是否是追踪型子弹
	static bool isTrackBullet(AttackType attackType);
	//是否是减速子弹
	static bool isDecelerationBullet(AttackType attackType);
	//是否是黄油子弹
	static bool isButterBullet(AttackType attackType);
protected:
	virtual void onHurt();
	void rotateInnerSprite();
	void dieAfterRunningAnimation(const string &animationName);
private:
	void hurt(int damage,AttackType attackType);
};
//-----------------------豌豆子弹PeaBullet------------------------------
class PeaBullet : public Bullet
{
public:
	CREATE_FUNC(PeaBullet);
	bool init();

	virtual void onHurt();
};
//---------------------爆炸Boom-------------------------
class Boom : public Bullet
{
	SDL_SYNTHESIZE(Rect,m_collisionRect,CollisionRect);
public:
	Boom();
	~Boom();
	CREATE_FUNC(Boom);
	bool init();

	virtual void contactEnd();
	virtual Rect getCollisionBoundingBox()const;
};
//------------------------CabbageBullet----------------------
class CabbageBullet : public Bullet
{
public:
	CREATE_FUNC(CabbageBullet);
	bool init();

	virtual void onHurt();
};
//------------------SnowPeaBullet----------------------------
class SnowPeaBullet : public Bullet
{
public:
	CREATE_FUNC(SnowPeaBullet);
	bool init();
	virtual void onHurt();
};
//-------------------FirePeaBullet----------------------------
class FirePeaBullet : public Bullet
{
private:
	bool m_bFirst;
	int m_nTime;
public:
	FirePeaBullet();
	CREATE_FUNC(FirePeaBullet);
	bool init();
	virtual void onHurt();
	virtual void contactEnd();
	virtual Rect getCollisionBoundingBox()const;
};
//-------------------FumeShroomBullet------------------------
class FumeShroomBullet : public Bullet
{
	SDL_SYNTHESIZE(float,m_fAtkScope,AtkScope);//攻击范围
public:
	FumeShroomBullet();
	CREATE_FUNC(FumeShroomBullet);
	bool init();

	virtual Rect getCollisionBoundingBox()const;
	virtual void contactEnd();
};
//-----------------ShroomBullet-----------------------------
class ShroomBullet : public Bullet
{
public:
	CREATE_FUNC(ShroomBullet);
	bool init();

	virtual void onHurt();
	virtual Rect getCollisionBoundingBox()const;
};
//------------------------CornBullet----------------------
class CornpultBullet : public Bullet
{
public:
	static CornpultBullet*create(bool isButter);
	bool init(bool isButter);

	virtual void onHurt();
};
#endif