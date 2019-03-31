#ifndef __Zombie_H__
#define __Zombie_H__
#include "Entity.h"
typedef enum ZombieStatus
{
	kZombieStatus_None,//无状态
	kZombieStatus_Idle,//站立状态
	kZombieStatus_Walk,//行走状态
	kZombieStatus_Attack,//攻击状态
	kZombieStatus_DeadAttack,//攻击死亡状态
	kZombieStatus_DeadWalk,//行走死亡状态
	kZombieStatus_DeadBomb,//炸死状态
	kZombieStatus_EntireDead//完全死亡状态
}ZombieStatus;
class Plant;
class HpBar;
class Zombie:public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//血量
	SDL_SYNTHESIZE(int,m_nDefense,Defense);//防御
	SDL_SYNTHESIZE(float,m_fSpeed,Speed);//移动速度
	SDL_SYNTHESIZE(ZombieStatus,m_status,ZombieStatus);//僵尸当前状态
	SDL_SYNTHESIZE(float,m_fSkillTime,SkillTime);//技能时间间隔
	SDL_SYNTHESIZE(float,m_showTime,ShowTime);//出现时机
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//当前流逝时间
	SDL_SYNTHESIZE(int,m_nRoute,Route);//路线
private:
	HpBar*m_pHpBar;
	Sprite*m_pHead;//僵尸头
public:
	Zombie();
	~Zombie();
	CREATE_FUNC(Zombie);
	bool init();

	void hurt(int damage);
	void dead();
	bool changeState(ZombieStatus status);
	//改变状态，并且运行相应动画
	bool runIdleAction();
	bool runWalkAction();
	bool runAttackAction();
	bool runLostHeadAction();//失去头运动动画
	bool runLostAttackAction();//攻击死亡动画
	bool runEntireDeadAction();
	bool runDeadBombAction();//被炸死

	virtual void onHurt();//受伤时调用
	virtual void onDead();//死亡时调用

	virtual void attack(Plant*plant,float dt);

	virtual FiniteTimeAction*onIdleAction();
	virtual FiniteTimeAction*onWalkAction();
	virtual FiniteTimeAction*onAttackAction();
	virtual FiniteTimeAction*onLostHeadAction();
	virtual FiniteTimeAction*onLostAttackAction();
	virtual FiniteTimeAction*onEntireDeadAction();
	virtual FiniteTimeAction*onHeadAction();
	virtual FiniteTimeAction*onDeadBombAction();
};
#endif