#ifndef __Fish_H__
#define __Fish_H__
#include<string>
#include "Entity.h"

typedef enum FishStatus
{
	FishStatus_None,//无状态
	FishStatus_Walk,//游动状态
	FishStatus_Scared,//受到惊吓状态
	FishStatus_Caught,//被捕状态
}FishStatus;

class Fish:public Entity
{
	SDL_SYNTHESIZE(int,m_nID,ID);//id
	SDL_SYNTHESIZE(std::string,m_name,Name);//名称
	SDL_SYNTHESIZE(std::string,m_desc,Description);//描述
	SDL_SYNTHESIZE(float,m_speed,Speed);//速度
	SDL_SYNTHESIZE(int,m_nWeightMean,WeightMean);//权数
	SDL_SYNTHESIZE(int,m_nGold,Gold);//金币
	SDL_SYNTHESIZE(Rect,m_colliableRect,ColliableRect);//碰撞体积
	SDL_SYNTHESIZE(Rect,m_scaredRect,ScaredRect);//惊吓体积
private:
	FishStatus m_status;
	Point m_endPos;
	int m_walkFrame;//运行帧
	int m_deadFrame;//死亡帧

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
	//获取鱼的警戒范围 世界坐标系
	/*Rect getScaredRect()const;
	//获取碰撞体积
	Rect getColliableRect()const;*/
private:
	bool changeStatus(FishStatus status);//切换鱼的当前状态
	//字符串转换为Rect
	Rect getRectFromString(const char*text);
};
#endif