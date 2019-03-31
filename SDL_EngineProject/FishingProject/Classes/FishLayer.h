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
	void linerRoute(Fish*pFish);//��ֱ��
	void bezierRoute(Fish*pFish);//�����������˶�
	void createNextFish();//������һ����Ҫ�ϳ�����
};
#endif