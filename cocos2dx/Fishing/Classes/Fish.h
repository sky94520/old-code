#ifndef __Fish_H__
#define __Fish_H__
#include<string>
#include "Entity.h"
#include "Box2D/Box2D.h"

typedef enum FishStatus
{
	FishStatus_None,//无状态
	FishStatus_Walk,//游动状态
	FishStatus_Scared,//受到惊吓状态
	FishStatus_Caught,//被捕状态
}FishStatus;

class Fish:public Entity
{
	CC_SYNTHESIZE(int,m_nID,ID);//id
	CC_SYNTHESIZE(std::string,m_name,FishName);//名称
	CC_SYNTHESIZE(std::string,m_desc,Description);//描述
	CC_SYNTHESIZE(float,m_speed,Speed);//速度
	CC_SYNTHESIZE(int,m_nWeightMean,WeightMean);//权数
	CC_SYNTHESIZE(int,m_nGold,Gold);//金币
	CC_SYNTHESIZE(Rect,m_colliableRect,ColliableRect);//碰撞体积
	CC_SYNTHESIZE(Rect,m_scaredRect,ScaredRect);//惊吓体积
	CC_SYNTHESIZE(float,m_elapsed,Elapsed);//什么时候上场

	CC_SYNTHESIZE(b2Body*,m_pScaredBody,ScaredBody);//惊吓刚体
	CC_SYNTHESIZE(b2Body*,m_pColliableBody,ColliableBody);//碰撞刚体
	
	CC_SYNTHESIZE(int,m_nRunningID,RunningID);//运行唯一标识符
private:
	FishStatus m_status;
	Point m_endPos;
	int m_walkFrame;//运行帧
	int m_deadFrame;//死亡帧
	Scheduler*m_pScheduler;
	ActionManager*m_pActionManager;

public:
	Fish();
	~Fish();
	CREATE_FUNC(Fish);
	static Fish*create(int id);

	bool init();
	bool init(int id);
	//正常游动动画
	void runNormalAnimation();
	//受到惊吓动画
	void runScaredAnimation();
	//被捕捉动画
	FiniteTimeAction*runCaughtAnimation();

	virtual FiniteTimeAction*onNormalAnimation();
	virtual FiniteTimeAction*onScaredAnimation();
	virtual FiniteTimeAction*onCaughtAnimation();
	//重置
	void reset();
	//鱼被捕捉
	void catched();
	FishStatus getStatus()const
	{
		return m_status;
	}
private:
	bool changeStatus(FishStatus status);//切换鱼的当前状态
	//字符串转换为Rect
	Rect getRectFromString(const char*text);
};
#endif