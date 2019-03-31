#ifndef __FishLayer_H__
#define __FishLayer_H__
#include<iostream>
#include "SDL_Engine/SDL_Engine.h"
class Fish;
using namespace SDL;

class FishLayer:public Layer
{
private:
	Vector<Fish*> m_fishes;
public:
	FishLayer();
	~FishLayer();
	CREATE_FUNC(FishLayer);
	bool init();
	virtual void update(float dt);
	Vector<Fish*>& getFishes();
private:
	void linerRoute(Fish*pFish);//鱼直线
	void bezierRoute(Fish*pFish);//贝塞尔曲线运动
	void createNextFish();//创建下一条将要上场的鱼
};
#endif