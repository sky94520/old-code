#ifndef __BackgroundLayer_H__
#define __BackgroundLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Carrier;
class BackgroundLayer:public Layer
{
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//流逝值
	SDL_SYNTHESIZE(float,m_skillCD,SkillCD);//产生太阳的间隔
	SDL_SYNTHESIZE(std::string,m_zombiePath,ZombiePath);//僵尸出场文件
private:
	Point m_startPos;//(256,80)为开始值
	Size m_size;//每个载体的大小
	Carrier*m_pCarriers[5][9];//植物载体
	Sprite*m_pBG;//背景
	bool m_bDay;//是否是白天
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	bool init();

	virtual void update(float dt);
	//加载场景
	void loadLevel(const std::string&level);
	//初始化技能释放时间
	void initSkillCD();
	//通过坐标值获取指定的载体
	Carrier*getCarrierByPos(const Point&pos);
	Rect getLegalRect()const;
	//是否是白天
	bool isDay()const;

};
#endif