#ifndef __GameScene_H__
#define __GameScene_H__
#include "cocos2d.h"
#include "TouchLayer.h"
#include "GameLayer.h"
#include "Box2D/Box2D.h"
class FishLayer;

USING_NS_CC;
class GameScene:public Scene,public TouchLayerDelegate,b2ContactListener
{
private:
	TouchLayer*m_pTouchLayer;
	GameLayer*m_pGameLayer;
	FishLayer*m_pFishLayer;

	CustomCommand _command;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();

	virtual void update(float dt);
private:
	//²æ×Ó
	virtual void shoot(const Point&targetPos);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
	void onDraw(const Mat4 &transform, uint32_t flags);
};
#endif