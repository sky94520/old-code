#ifndef __Plant_H__
#define __Plant_H__
#include<string>
#include "Entity.h"

typedef enum PlantType
{
	kPlantType_Shooter,//豌豆射手 寒冰射手 仙人掌
	kPlantType_Producer, //向日葵
	kPlantType_Wall,     //各种墙 如坚果墙 大坚果墙
	kPlantType_Bomb     //炸弹 如樱桃炸弹
}PlantType;
class Plant:public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//总血量
	SDL_SYNTHESIZE(int,m_nCurHP,CurHP);//当前血量
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//流逝值
	SDL_SYNTHESIZE(float,m_interval,Interval);//技能间隔时间
	SDL_SYNTHESIZE(int,m_nLine,Line);//该植物所在行数
public:
	Plant();
	~Plant();
	void hurt(int damage);//受伤时调用
	void dead();//死亡时调用
	bool isDead()const;//是否死亡

	//动画级操作都是对m_pSprite而言
	virtual FiniteTimeAction*onNormalAction()=0;//正常动画
	virtual FiniteTimeAction*onSkillAction()=0;//技能动画
	virtual void onHurt()=0;
	virtual void onDead()=0;
	virtual void initInterval()=0;
	virtual PlantType getPlantType()const=0;
	virtual std::string getName()const=0;
};
#endif