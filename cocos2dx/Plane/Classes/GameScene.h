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
	//����ʹ��
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

	virtual void BeginContact(b2Contact* contact);//�ڿ�ʼ��ײʱ����
	void onTouchMoved(Touch*touch,Event*event);
	virtual void shootTo(const Vec2&startPos);
	void gamePause();
	void gameResume();
	void gameRestart();
	void gameEnd();
	void gameOver();//��Ϸ������������ʱ����
	void operateAllSchedulerAndActions(Node*target,bool paused);
private:
	//����
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	void onDraw(const kmMat4 &transform,bool transformUpdated);
};
#endif