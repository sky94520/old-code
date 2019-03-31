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

	//展示僵尸死亡动画
	void showZombieDie(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	void showZombieBoom(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	void showZombieHead(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX);
	void showGarnishryFallAction(Layer*layer,const string&spriteName,const Point&pos,int localZOrder,bool flipX);

	//展示土壤上升动画
	void showRisingDirt(const Point&pos,Layer*layer,int localZOrder);
	//显示 土豆雷 唏噗
	void showExplosionSpudow(const Point&pos,Layer*layer,int localZOrder);
	//添加黄油特效
	void addButterSplat(const Point&pos,Layer*layer,int localZOrder,int uniqueID);
	void removeButterSplat(Layer*layer,int uniqueID);
	//添加冰冻特效
	void addIceTrap(const Point&pos,Layer*layer,int localZOrder,int uniqueID);
	void removeIceTrap(Layer*layer,int uniqueID);
	//添加饰品特效
	void addGarnishryEffect(int id,const Point&pos,const string&str,Layer*layer,int localZOrder);
	void removeGarnishryEffect(Layer*layer,int uniqueID);
	//展示咖啡豆被吃动画
	float showCoffeeBeanEatAction(const Point&pos,Layer*layer,int localZOrder);
	//展示雪花特效
	void showSnow(const Point&pos,Layer*layer,int localZOrder);
	//展示炸
	void showBoom(const Point&pos,Layer*layer,int localZOrder);
	//展示火 动画
	void showFire(const Point&pos,Layer*layer,int localZOrder);
private:
	Sprite*runEffectWithAnimationName(const string&animationName,const Point&pos
		,Layer*layer,int tag,const Point&anchorPoint = Point(0.5f,0.5f));
	Sprite*runEffectWithRotate(const string&spriteName,float duration);
};
#endif