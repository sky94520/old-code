#include "GameScene.h"
#include "Player.h"
#include "ItemLayer.h"
#include "PanelLayer.h"
#include "HomeScene.h"
#include "GB2ShapeCache-x.h"
GameScene::GameScene()
	:m_pWorld(nullptr),m_pMenuLayer(nullptr),
	m_pPanelLayer(nullptr),m_pEnemyLayer(nullptr)
	,m_pTouchLayer(nullptr),m_pGameLayer(nullptr)
	,m_pBulletLayer(nullptr),m_pItemLayer(nullptr)
{
}
GameScene::~GameScene()
{
	CC_SAFE_DELETE(m_pWorld);
	CC_SAFE_DELETE(m_debugDraw);
}
bool GameScene::init()
{
	ActionManager::
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//初始化物理引擎
	initPhysics();

	auto bg = TMXTiledMap::create("map/blue_bg.tmx");
	this->addChild(bg,-1);
	//菜单层
	m_pMenuLayer = MenuLayer::create();
	m_pMenuLayer->setVisible(false);
	m_pMenuLayer->setDelegate(this);
	this->addChild(m_pMenuLayer);
	//敌人层
	m_pEnemyLayer = EnemyLayer::create();
	m_pEnemyLayer->setDelegate(this);
	this->addChild(m_pEnemyLayer);
	//添加显示层
	m_pPanelLayer = PanelLayer::create();
	m_pPanelLayer->setDelegate(this);
	this->addChild(m_pPanelLayer);
	//添加触摸层
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//游戏层
	m_pGameLayer = GameLayer::create(this);
	this->addChild(m_pGameLayer);
	//子弹层
	m_pBulletLayer = BulletLayer::create();
	m_pBulletLayer->setDelegate(this);
	this->addChild(m_pBulletLayer);
	//道具层
	m_pItemLayer = ItemLayer::create(this);
	this->addChild(m_pItemLayer);
	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	m_pEnemyLayer->update(dt);
	m_pItemLayer->update(dt);
	m_pPanelLayer->update(dt);
	//物理
	m_pWorld->Step(dt,8,8);
	for(b2Body*body = m_pWorld->GetBodyList();body;body = body->GetNext())
	{
		if(body->GetUserData())
		{
			auto*sprite = static_cast<Entity*>(body->GetUserData());
			auto p = sprite->getPosition();
			b2Vec2 pos = b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO);
			float32 angle = -CC_DEGREES_TO_RADIANS(sprite->getSprite()->getRotation());
			body->SetTransform(pos,angle);
		}
	}
}
void GameScene::initPhysics()
{
	//重力
	b2Vec2 gravity;
	gravity.Set(0.f,0.f);
	m_pWorld = new b2World(gravity);
	m_pWorld->SetAllowSleeping(true);
	m_pWorld->SetContinuousPhysics(true);
	m_pWorld->SetContactListener(this);
	//暂时不设置边界
	//开启调试
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);
	m_pWorld->SetDebugDraw(m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);
}
void GameScene::bindPhysicalBody(void*userdata,const MyBody&myBody,b2Shape*shape)
{
	b2BodyDef bodyDef;
	bodyDef.type = myBody.type; 
	bodyDef.position = myBody.position;
	bodyDef.bullet = true;

	b2Body*body = m_pWorld->CreateBody(&bodyDef);
	body->SetUserData(userdata);
	//创建夹具
	b2FixtureDef fixtureDef;
	fixtureDef.density = myBody.density;
	fixtureDef.friction = myBody.firction;
	fixtureDef.shape = shape;
	fixtureDef.filter.categoryBits = myBody.categoryBits;
	fixtureDef.filter.maskBits = myBody.maskBits;

	body->CreateFixture(&fixtureDef);
}
void GameScene::bindPhysicalBody(void*userdata,const std::string&shape,b2BodyDef*bodyDef)
{
	b2Body*body = m_pWorld->CreateBody(bodyDef);
	GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(body,shape);
	body->SetUserData(userdata);
}
void GameScene::BeginContact(b2Contact* contact)
{
	b2Body*body1 = contact->GetFixtureA()->GetBody();
	b2Body*body2 = contact->GetFixtureB()->GetBody();
	 
	auto entity1 = static_cast<Entity*>(body1->GetUserData());
	auto entity2 = static_cast<Entity*>(body2->GetUserData());

	if(entity1->isAlive() && entity1->isVisible()
		&& entity2->isAlive() && entity2->isVisible())
	{
		int damage1 = entity1->getDamage();
		int damage2 = entity2->getDamage();
		entity1->hurt(damage2);
		entity2->hurt(damage1);
	}
}
void GameScene::onTouchMoved(Touch*touch,Event*event)
{
	m_pGameLayer->move(touch,event);
}
void GameScene::shootTo(const Vec2&startPos)
{
	m_pBulletLayer->shootTo(startPos);
}
void GameScene::gamePause()
{
	m_pMenuLayer->setVisible(true);
	this->unscheduleUpdate();
	operateAllSchedulerAndActions(m_pGameLayer,true);
	operateAllSchedulerAndActions(m_pTouchLayer,true);
	operateAllSchedulerAndActions(m_pBulletLayer,true);
	operateAllSchedulerAndActions(m_pEnemyLayer,true);
	operateAllSchedulerAndActions(m_pItemLayer,true);

}
void GameScene::gameResume()
{
	m_pMenuLayer->setVisible(false);

	this->scheduleUpdate();
	operateAllSchedulerAndActions(m_pGameLayer,false);
	operateAllSchedulerAndActions(m_pTouchLayer,false);
	operateAllSchedulerAndActions(m_pBulletLayer,false);
	operateAllSchedulerAndActions(m_pEnemyLayer,false);
	operateAllSchedulerAndActions(m_pItemLayer,false);
}
void GameScene::gameRestart()
{
	Director::getInstance()->replaceScene(GameScene::create());
}
void GameScene::gameEnd()
{
	Director::getInstance()->replaceScene(HomeScene::create());
}
void GameScene::gameOver()
{
	GameScene::gamePause();
	m_pMenuLayer->gameOver();
}
void GameScene::operateAllSchedulerAndActions(Node*target,bool paused)
{
	if(target == nullptr)
		return ;
	if(paused)
	{
		target->pauseSchedulerAndActions();
	}
	else
	{
		target->resumeSchedulerAndActions();
	}
	auto children = target->getChildren();
	for(int i=0;i<children.size();i++)
		operateAllSchedulerAndActions(children.at(i),paused);
}
void GameScene::draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(GameScene::onDraw,this,transform,flags);
	renderer->addCommand(&_customCommand);
}
void GameScene::onDraw(const kmMat4 &transform,bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	m_pWorld->DrawDebugData();
	//结束绘制
	kmGLPopMatrix();
}