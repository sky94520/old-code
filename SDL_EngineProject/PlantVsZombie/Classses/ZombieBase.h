#ifndef __ZombieBase_H__
#define __ZombieBase_H__
#include<string>
#include<vector>
#include<algorithm>
#include "Character.h"

using namespace std;

class HpBar;
class Plant;
class Terrain;
class MoveBehavior;
class Garnishry;
class Bullet;
class ZombieBase;

class ZombieDelegate
{
public:
	virtual Plant*getTopPlant(Terrain*terrain) = 0;
	
	virtual void addButterSplat(const Point&pos,int localZOrder,int uniqueID)=0;
	virtual void removeButterSplat(int uniqueID)=0;

	virtual void addIceTrap(const Point&pos,int localZOrder,int uniqueID)=0;
	virtual void removeIceTrap(int uniqueID)=0;

	virtual void showRisingDirt(const Point&pos,int localZOrder) = 0;

	virtual void showZombieDie(const string& zombieName,const Point&pos,int localZOrder,bool flipX) = 0;
	virtual void showZombieBoom(const string& zombieName,const Point&pos,int localZOrder,bool flipX) = 0;
	virtual void showZombieHead(const string& zombieName,const Point&pos,int localZOrder,bool flipX) = 0;
	virtual void showGarnishryFallAction(Garnishry*garnishry,const Point&pos,int localZOrder,bool flipX) = 0;

	virtual ZombieBase*makeZombie(const string& zombieName,const Point&pos,int row,bool bConfused) = 0;
};
/*僵尸的减益效果*/
enum class DebuffType
{
	Deceleration,
	Butter,
	Ice,
};
typedef struct Debuff
{
	DebuffType type;
	float duration;
public:
	Debuff(DebuffType type,float d):type(type),duration(d){}
}Debuff;

class ZombieBase : public Character
{
	SDL_SYNTHESIZE(float,m_fCriticalPoint,CriticalPoint);//临界点
	SDL_SYNTHESIZE(float,m_fBaseSpeed,BaseSpeed);//基础移动速度
	SDL_SYNTHESIZE(string,m_zombieName,ZombieName);//僵尸名称
	SDL_SYNTHESIZE(float,m_fColdDownTime,ColdDownTime);//攻击冷却时间
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//伤害值
	SDL_BOOL_SYNTHESIZE(m_bConfused,Confused);//是否被迷惑
protected:
	Character*m_pAim;//当前目标
	ZombieDelegate*m_pDelegate;
	MoveBehavior*m_pMoveBehavior;
	HpBar*m_pHpBar;
	Garnishry*m_pGarnishry;//饰品
	vector<Debuff> m_debuffs;//当前的僵尸的debuff
	int m_nRow;
	Rect m_vertexBox;//顶点包围盒
private:
	float m_eatingElapsed;
	bool _isDying;//当前僵尸是否已经死亡
public:
	ZombieBase();
	~ZombieBase();
	//设置委托
	void setDelegate(ZombieDelegate*pDelegate);
	//设置当前行数
	void setRow(int row);
	//设置当前目标
	void setAim(Character*character);
	Character*getAim();
	//清除目标
	void clearAim();
	//吃目标
	void eatAim(float dt);
	//添加饰品
	void addGarnishry(Garnishry*garnishry);
	//移除饰品
	//void removeGarnishry(Garnishry*garnishry);
	Garnishry*getGarnishry();
	//覆盖父函数，加入临界点
	bool isDying()const;
	//设置顶点包围盒
	void setVertexBox(const Rect&rect);
	Rect getVertexBox()const;

	virtual Rect getCollisionBoundingBox()const;
	//重写受伤回调函数
	void hurt(int baseDamage,AttackType attackType);
	//减速
	void deceleration(AttackType type,float duration);
	//黄油
	void butter(const Point&pos,float duration);
	//冰冻
	void ice(float duration);
	//设置移动行为
	void setMoveBehavior(MoveBehavior*behavior);
	MoveBehavior*getMoveBehavior();
	//绑定血量条
	void bindHpBar(HpBar*hpBar);
	//是否处于某一种debuff下
	bool isDuringDebuff(DebuffType debuffType)const;
	//是否处于减速状态
	bool isDuringDeceleration()const;
	//处于黄油状态
	bool isDuringButter()const;
	//是否处于冰冻状态
	bool isDuringIce()const;
	//是否暂停 当处于黄油或者冰冻debuff时，处于暂停状态
	bool isPausedLogic()const;
	//获取当前行数
	virtual int getRow()const;
	//获取当前速度
	virtual float getCurSpeed()const;
	//更新回调函数
	virtual void update(float dt);
	//是否参与与子弹的碰撞，不包括Boom
	virtual bool isActiveForBullet()const;
	//改变贴图为右
	virtual void setSpriteFlipX(bool flipX);
protected:
	//活着更新函数
	virtual void updateAlive(float dt) = 0;
	//僵尸是否可移动
	virtual bool isCanMove()const;
	//受伤回调函数
	virtual void onHurt();
	//吞噬死亡回调函数
	virtual void onSwallowDead();
	//炸死回调函数
	virtual void onBoomDead();
	//死亡回调函数
	virtual void onNormalDead();
	//临界点死亡即为0回调函数
	virtual void onCRPDead();
	//饰品死亡函数
	virtual void onGarnishryDead();
	//减速debuff开始动画必须经过Speed包装
	virtual void onDecelerationDebuffEnter();
	//减速debuff结束
	virtual void onDecelerationDebuffExit();
	//减速debuff黄油 开始
	virtual void onButterDebuffEnter(const Point&pos);
	//减速debuff黄油 结束
	virtual void onButterDebuffExit();
	//冰冻开始
	virtual void onIceDebuffEnter();
	virtual void onIceDebuffExit();
private:
	//受伤动画
	void showHurtAction();
	//消除某一类型的debuff
	void removeDebuff(DebuffType debuffType);
	vector<Debuff>::iterator removeDebuff(vector<Debuff>::iterator it);
	void removeAllDebuff();
	//尝试添加debuff
	void  addDebuff(Debuff debuff,const function<void ()> &callback);
	void updateDebuff(float dt);
protected:
	//切换动画函数
	void changeAnimation(Animation*animation);
};
#endif