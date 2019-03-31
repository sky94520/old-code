#ifndef __GameScene_H__
#define __GameScene_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "EnemyLayer.h"
#include "TouchLayer.h"
#include "BulletLayer.h"
#include "GameLayer.h"
#include "PanelLayer.h"
#include "MenuLayer.h"
#define PTM_RATIO 32
USING_NS_CC;
class ItemLayer;
class GameScene:public Scene,public b2ContactListener
	,TouchLayerDelegate,BulletLayerDelegate,GameLayerDelegate
	,PanelLayerDelegate,MenuLayerDelegate
{
private:
	b2World*m_pWorld;
	MenuLayer*m_pMenuLayer;
	PanelLayer*m_pPanelLayer;
	EnemyLayer*m_pEnemyLayer;
	TouchLayer*m_pTouchLayer;
	GameLayer*m_pGameLayer;
	BulletLayer*m_pBulletLayer;
	ItemLayer*m_pItemLayer;
	//调试使用
	GLESDebugDraw*m_debugDraw;
	CustomCommand _customCommand;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	virtual void update(float dt);
private:
	void initPhysics();

	void bindPhysicalBody(void*userdata,const MyBody&myBody,b2Shape*shape);
	void bindPhysicalBody(void*userdata,const std::string&shape,b2BodyDef*bodyDef);

	virtual void BeginContact(b2Contact* contact);//在开始碰撞时调用
	void onTouchMoved(Touch*touch,Event*event);
	virtual void shootTo(const Vec2&startPos);
	void gamePause();
	void gameResume();
	void gameRestart();
	void gameEnd();
	void gameOver();//游戏结束，在死亡时调用
	void operateAllSchedulerAndActions(Node*target,bool paused);
private:
	//调试
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	void onDraw(const kmMat4 &transform,bool transformUpdated);
};
#endif