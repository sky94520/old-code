#ifndef __Rocker_H__
#define __Rocker_H__
#include<string>
#include "cocos2d.h"
class Hero;
using namespace cocos2d;

class Rocker:public Node
{
private:
	//摇杆与摇杆背景
	Sprite*m_pRocker;
	Sprite*m_pRockerBG;
	//方向 
	Point m_cDirection;
	//是否启用
	bool m_bIsActive;
	//事件监听器
	EventListenerTouchOneByOne*m_pTouchListener;
	//是否可移动
	bool m_bCanMove;
public:
	Rocker();
	CREATE_FUNC(Rocker);
	static Rocker*createRocker(std::string rockerFileName,std::string rockerBGFileName,const Point*position);
	virtual bool init();
	bool initRocker(std::string rockerFileName,std::string rockerBGFileName,const Point*position);
	//开始/禁用 摇杆
	void start();
	void stop();
	//获得偏移量
	Point getDirection();
	//
	virtual bool onTouchBegan(Touch*touch,Event*e);
	virtual void onTouchMoved(Touch*touch,Event*e);
	virtual void onTouchEnded(Touch*touch,Event*e);
};
#endif