#ifndef __GameLayer_H__
#define __GameLayer_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SystemHeader.h"
USING_NS_CC;
class Player;
class GameLayerDelegate
{
public:
	virtual ~GameLayerDelegate(){}
	virtual void shootTo(const Vec2&startPos)=0;
	virtual void bindPhysicalBody(void*userdata,const MyBody&myBody,b2Shape*shape)=0;
	virtual void bindPhysicalBody(void*userdata,const std::string&shape,b2BodyDef*bodyDef)=0;
	virtual void gameOver()=0;
};
class GameLayer:public Layer
{
private:
	Player*m_pPlayer;//Íæ¼Ò·É»ú;
	GameLayerDelegate*m_pDelegate;
public:
	GameLayer();
	~GameLayer();
	bool init(GameLayerDelegate*pDelegate);
	static GameLayer*create(GameLayerDelegate*pDelegate);
	//Playerº¯Êý
	void move(Touch*touch,Event*event);
	//
	void shootTo(float dt);
	void gameOver(Ref*);
};
#endif