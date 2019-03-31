#ifndef __Enemy_H__
#define __Enemy_H__
#include "BehaviorEntity.h"
#include "SDL_Engine/SDL_Engine.h"
#include "EnemyLayer.h"

using namespace SDL;

class MoveBehavior;
class Player;

enum class EnemyHurtType
{
	None,//未受到伤害
	Bullet,//被子弹所伤害
	Stamp,//被mario踩到
	Star,//受到星星的伤害
	Enemy,//受到敌人的伤害
};
/*一切敌人的基类*/
class Enemy:public BehaviorEntity
{
	SDL_BOOL_SYNTHESIZE(m_bBulletImmune,BulletImmune);//是否对子弹免疫
	SDL_BOOL_SYNTHESIZE(m_bStampImmune,StampImmune);//是否对踩免疫，是则会伤害mario
	SDL_BOOL_SYNTHESIZE(m_bStarImmune,StarImmune);//是否对星星免疫
	SDL_BOOL_SYNTHESIZE(m_bEnemyImmune,EnemyImmune);//是否对敌人造成的伤害免疫
	SDL_BOOL_SYNTHESIZE(m_bCanHurtEnemy,CanHurtEnemy);//是否会伤害敌人
	SDL_BOOL_SYNTHESIZE(m_bCollidedWithEnemyFlag,CollidedWithEnemyFlag);//碰撞标记，避免重复碰撞
	SDL_BOOL_SYNTHESIZE(m_bCollidedWithPlayerFlag,CollidedWithPlayerFlag);
protected:
	static const int ENEMY_ANIMATION_TAG;//动画只能运行一个
public:
	Enemy();
	~Enemy();
	//处理血量
	void hurt(Entity*entity,EnemyHurtType hurtType);
	//处理内部状态 返回值 为true则尝试进行扣血判断
	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	//改变x轴方向，仅仅是方向
	virtual void changeDirectionX();

	virtual void onDead(EnemyHurtType hurtType)=0;
	virtual void runRunnableAnimation()=0;//正常行走动画
	virtual bool tileCollidedX(bool bRight)=0;
	virtual bool tileCollidedY(bool bDown)=0;
};
//-----------------------------三角蘑菇-----------------------------------
class TriMushroom:public Enemy
{
public:
	TriMushroom();
	~TriMushroom();
	CREATE_FUNC(TriMushroom);
	bool init();

	virtual void onDead(EnemyHurtType hurtType);

	virtual void runRunnableAnimation();
	virtual Rect getCollisionBoundingBox()const;

	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
};
//---------------------------- Tortoise----------------------------
class Tortoise:public Enemy
{
	SDL_SYNTHESIZE(Point,m_oldVelocity,OldVelocity);//保存着乌龟一开始的速度
public:
	enum TortoiseStateType
	{
		kTortoiseState_Run,//运动状态
		kTortoiseState_SinkHead,//缩头状态
		kTortoiseState_RunAndSinkHead,//缩头并且正在运动
	};
private:
	float m_ressurectTime;//复活时间
	const static string m_ressurectScheduleStr;//复活计时器名称
	TortoiseStateType m_stateType;//状态类型
	bool m_bLeft;//当前是否正在向左
public:
	Tortoise();
	~Tortoise();
	CREATE_FUNC(Tortoise);
	bool init();

	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	virtual void onDead(EnemyHurtType hurtType);

	virtual bool isInteractiveWithBlock()const;
	virtual bool isCanBrokeTile()const;

	virtual void runRunnableAnimation();
	virtual Rect getCollisionBoundingBox()const;

	virtual void changeDirectionX();
	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
private:
	void ressurectPeriodOne();//重生阶段1
	void ressurectPeriodTwo(float dt);//重生阶段2 此时
	void ressurectPeriodThree(float dt);//重生阶段3
};
//--------------------------------WingEnemyDecorator翅膀装饰者-----------------
class WingEnemyDecorator:public Enemy
{
private:
	Enemy*m_pInnerEnemy;
	bool m_bWingDead;//翅膀是否死亡
	float const MAX_JUMP_HEIGHT;//星星跳跃的最高距离
	float m_curJumpHeight;
	//当前运动方向是否向左
	bool m_bLeft;
public:
	WingEnemyDecorator();
	~WingEnemyDecorator();
	static WingEnemyDecorator*create(Enemy*enemy);
	bool init(Enemy*enemy);

	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	virtual void onDead(EnemyHurtType hurtType);
	virtual void changeDirectionX();
	virtual bool isInteractiveWithBlock()const;
	virtual bool isCanBrokeTile()const;

	virtual void runRunnableAnimation();
	virtual Rect getCollisionBoundingBox()const;
	virtual void performMove(float dt);

	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
};
//-----------------------------Chomper---------------------------------
class Chomper:public Enemy
{
	SDL_SYNTHESIZE(float,m_maxJumpHeight,MaxJumpHeight);
	SDL_SYNTHESIZE(Rect,m_shapeRect,ShapeRect);
private:
	float m_curJumpHeight;
	float m_delayTime;//到最高点的停留时间
	float m_elpased;//流逝时间
	EnemyDelegate*m_pDelegate;
public:
	Chomper();
	~Chomper();
	CREATE_FUNC(Chomper);
	bool init();

	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	virtual void onDead(EnemyHurtType hurtType);

	virtual void runRunnableAnimation();//正常行走动画
	virtual void performMove(float dt);

	virtual bool tileCollidedX(bool bRight){return false;}
	virtual bool tileCollidedY(bool bDown){return false;}

	void setDelegate(EnemyDelegate*pDelegate);
};
#endif