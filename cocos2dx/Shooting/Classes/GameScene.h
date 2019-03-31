#ifndef __GameScene_H__
#define __GameScene_H__
#include "cocos2d.h"
#include "TiledMapLayer.h"
#include "GameLayer.h"
#include "TouchLayer.h"
USING_NS_CC;
class BackgroundLayer;
class GameScene:public Scene,public GameLayerDelegate,TouchLayerDelegate
{
private:
	BackgroundLayer*m_pBackgroundLayer;
	TiledMapLayer*m_pTiledMapLayer;
	GameLayer*m_pGameLayer;
	TouchLayer*m_pTouchLayer;
public:
	GameScene();
	~GameScene();
	bool init();
	CREATE_FUNC(GameScene);
	virtual void update(float dt);
private:
	ValueMap getObject(const std::string&name);
	void arrowAimAt(const Point&pos);
	void arrowShootTo(const Point&pos);
private:
	void checkCollistion();

};
#endif