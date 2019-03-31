#ifndef __Player_H__
#define __Player_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"
#include "Item.h"

using namespace std;
using namespace SDL;
//主角当前状态
enum PlayerState
{
	kPlayerState_None,
	kPlayerState_Idle,//站立状态
	kPlayerState_Runnable,//跑
	kPlayerState_Jumping,//跳
	kPlayerState_Falling,//下落
	kPlayerState_Dead,//死亡
	kPlayerState_Sit,//蹲下状态
};
//主角无敌的类型
enum class InvulnerableType
{
	kNone,//正常状态
	kWithoutCollision,//不参与碰撞
	kCanHurtEnemy,//参与碰撞，并且会伤害敌人
};
class Player:public Entity
{
	SDL_SYNTHESIZE(float,m_moveSpeed,MoveSpeed);//移动速度
	SDL_BOOL_SYNTHESIZE(m_bCanJump,CanJump);//是否能跳
	SDL_BOOL_SYNTHESIZE(m_bJumping,Jumping);//当前是否处于正在跳的状态
	SDL_SYNTHESIZE(PlayerState,m_curState,CurState);//当前状态
	SDL_SYNTHESIZE(int,m_curLevel,CurLevel);//级别 0 最小 1 大 2 大会发射子弹
	SDL_SYNTHESIZE(InvulnerableType,m_invulnerableType,InvulnerableType);//设置无敌的类型
	SDL_SYNTHESIZE(int,m_bulletNum,BulletNum);
private:
	const static int ANIMATION_TAG;//主角动画的tag
private:
	float m_invulnerableTime;//复活后的无敌时间
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	bool init();
	//站立
	void idle();
	void fall();//下落
	void run(bool bRight = true);
	void jump();
	void sit();
	//复活
	void ressurect(float invulnerableTime);
	void runIdleAnimation();//站立动画
	void runRunnableAnimation();//运动动画
	void runJumpingAnimation();//跳动画
	void runSittingAnimation();//做下动作
	void runDeadAnimation();//死亡动画
	//主角是否无敌
	bool isInvulnerable()const;
	//升级
	void levelUp();
	//降级
	void levelDown();
	//使主角能伤害敌人并且自己不会受伤
	void canHurtEnemyWithInvulnearability();
	//获取成长所需要的道具类型
	ItemType getGrowingItemType()const;
	//获取主角当前朝向 当前朝向是否向右 跟图片资源有关
	bool isDirRight()const;
	//子弹死亡回调函数
	void bulletOver(EventCustom*);
	//当前主角是否可以发射子弹
	bool isCanShoot()const;

	virtual void onBindSprite();
	virtual bool onHurt(int damage);
	virtual void onDead();
	virtual	Rect getCollisionBoundingBox()const;

	virtual bool isInteractiveWithBlock()const;
	virtual bool isCanBrokeTile()const;
private:
	bool changeState(PlayerState nextState);
	//使mario无敌 无敌类型，无敌时间
	void makeSelfInvulnerable(InvulnerableType type,float invulnerableTime);
	//无敌后的函数回调
	//void endInvulnearableCallback(float elpased);
};
#endif