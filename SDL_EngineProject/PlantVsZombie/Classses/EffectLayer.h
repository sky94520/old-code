#ifndef __EffectLayer_H__
#define __EffectLayer_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;

class EffectLayer : public Layer
{
public:
	CREATE_FUNC(EffectLayer);
	bool init();

	//չʾ��ʬ��������
	void showZombieDie(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	void showZombieBoom(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	void showZombieHead(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	void showGarnishryFallAction(Layer*layer,const string&spriteName,const Point&pos,int localZOrder,bool flipX);

	//չʾ������������
	void showRisingDirt(const Point&pos,Layer*layer,int localZOrder);
	//��ʾ ������ ����
	void showExplosionSpudow(const Point&pos,Layer*layer,int localZOrder);
	//��ӻ�����Ч
	void addButterSplat(const Point&pos,Layer*layer,int localZOrder,int uniqueID);
	void removeButterSplat(Layer*layer,int uniqueID);
	//��ӱ�����Ч
	void addIceTrap(const Point&pos,Layer*layer,int localZOrder,int uniqueID);
	void removeIceTrap(Layer*layer,int uniqueID);
	//�����Ʒ��Ч
	void addGarnishryEffect(int id,const Point&pos,const string&str,Layer*layer,int localZOrder);
	void removeGarnishryEffect(Layer*layer,int uniqueID);
	//չʾ���ȶ����Զ���
	float showCoffeeBeanEatAction(const Point&pos,Layer*layer,int localZOrder);
	//չʾѩ����Ч
	void showSnow(const Point&pos,Layer*layer,int localZOrder);
	//չʾը
	void showBoom(const Point&pos,Layer*layer,int localZOrder);
	//չʾ�� ����
	void showFire(const Point&pos,Layer*layer,int localZOrder);
private:
	Sprite*runEffectWithAnimationName(const string&animationName,const Point&pos
		,Layer*layer,int tag,const Point&anchorPoint = Point(0.5f,0.5f));
	Sprite*runEffectWithRotate(const string&spriteName,float duration);
};
#endif