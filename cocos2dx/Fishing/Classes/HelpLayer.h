#ifndef __HelpLayer_H__
#define __HelpLayer_H__
#include "cocos2d.h"
USING_NS_CC;
/*捕鱼辅助界面*/
/*
need:
	1.能获取场上的鱼的状态	
	2.能获得鱼叉的状态
*/
/*接收触碰消息，必要时会吞掉，当发生触碰事件时，如果如果和HelpfulComponent
发生碰撞，就执行相应操作，并吞并事件，默认组件是不展开的，且每次捕鱼都会使组件不展开
如果捕到鱼，就显示相应的过关条件
*/
class Fish;
class Fork;
class HelpfulFish;

class HelpLayerDelegate
{
public:
	virtual ~HelpLayerDelegate(){}
	virtual Vector<Fish*>* getShowingFishes()= 0;
	virtual Fork*getShowingFork() = 0;
};
class HelpLayer:public Layer
{
private:
	HelpLayerDelegate*m_pDelegate;
	int m_nLength;
public:
	HelpLayer();
	~HelpLayer();
	CREATE_FUNC(HelpLayer);
	bool init();
	void setDelegate(HelpLayerDelegate*m_pDelegate);
	/*绘制,在onDraw中调用*/
	void debugDraw();
	//在小窗口显示渔叉
	void showHelpfulFork(const Point&pos);

	virtual void update(float dt);
private:
	HelpfulFish*getHelpfulFishByTag(int tag);
};
#endif