#ifndef __FishLayer_H__
#define __FishLayer_H__
#include<iostream>
#include "cocos2d.h"
class Fish;
USING_NS_CC;
class FishLayer:public Layer
{
private:
	Vector<Fish*> m_fishes;//�������е���
	Vector<Fish*> m_showingFishes;//�ڳ��ϵ���
	Vector<Fish*> m_willShowFishes;//��Ҫ��������
public:
	FishLayer();
	~FishLayer();
	CREATE_FUNC(FishLayer);
	bool init();
	void reset();
	virtual void update(float dt);
	Vector<Fish*>* getFishes();
private:
	void linerRoute(Fish*pFish);//��ֱ��
	void bezierRoute(Fish*pFish);//�����������˶�
	//������һ����Ҫ�ϳ����� id��ʱ��
	void initFish(Fish*pFish);
};
#endif