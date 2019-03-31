#ifndef __FishLayer_H__
#define __FishLayer_H__
#include<iostream>
#include "cocos2d.h"
class Fish;
USING_NS_CC;
class FishLayer:public Layer
{
private:
	Vector<Fish*> m_fishes;//保存所有的鱼
	Vector<Fish*> m_showingFishes;//在场上的鱼
	Vector<Fish*> m_willShowFishes;//将要出场的鱼
public:
	FishLayer();
	~FishLayer();
	CREATE_FUNC(FishLayer);
	bool init();
	void reset();
	virtual void update(float dt);
	Vector<Fish*>* getFishes();
private:
	void linerRoute(Fish*pFish);//鱼直线
	void bezierRoute(Fish*pFish);//贝塞尔曲线运动
	//创建下一条将要上场的鱼 id，时间
	void initFish(Fish*pFish);
};
#endif