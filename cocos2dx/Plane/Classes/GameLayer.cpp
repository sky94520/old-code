#include "GameLayer.h"
#include "Player.h"
#include "SystemHeader.h"
#include "StaticData.h"
#include "EnemyLayer.h"
#include "DynamicData.h"
GameLayer::GameLayer()
	:m_pPlayer(nullptr),m_pDelegate(nullptr)
{
}
GameLayer::~GameLayer()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(GameLayer::shootTo));
	NotificationCenter::getInstance()->removeObserver(this,"player sub");
}
GameLayer*GameLayer::create(GameLayerDelegate*pDelegate)
{
	auto layer = new GameLayer();
	if(layer && layer->init(pDelegate))
		layer->autorelease();
	else
		CC_SAFE_DELETE(layer);
	return layer;
}
bool GameLayer::init(GameLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	const int PTM_RATIO = StaticData::getInstance()->getValueForKey("PTM_RATIO").asInt();
	//添加player
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(visibleSize.width/2,m_pPlayer->getContentSize().height);
	this->addChild(m_pPlayer);
	//添加物理引擎
	/*MyBody myBody;
	myBody.type = b2_dynamicBody;
	myBody.density = 0.1f;
	myBody.firction = 0.2f;
	myBody.categoryBits = 0x02;
	myBody.maskBits = 0x01 + 0x06;
	//形状
	b2Shape*shape1 = new b2CircleShape();
	shape1->m_radius = m_pPlayer->getContentSize().width/PTM_RATIO/2;*/
	//pDelegate->bindPhysicalBody(m_pPlayer,myBody,shape1);
	//int PTM_RATIO = 
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_pPlayer->getPosition().x/PTM_RATIO,m_pPlayer->getPosition().y/PTM_RATIO);
	pDelegate->bindPhysicalBody(m_pPlayer,"plane1",&bodyDef);
	//添加计时器，定时发射子弹
	this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::shootTo),0.2f,-1,0);
	//添加监听器
	NotificationCenter::getInstance()->addObserver(this,
		CC_CALLFUNCO_SELECTOR(GameLayer::gameOver),"player sub",nullptr);
	return true;
}
void GameLayer::move(Touch*touch,Event*event)
{
	m_pPlayer->onTouchMoved(touch,event);
}
void GameLayer::shootTo(float dt)
{
	Size size = m_pPlayer->getContentSize();
	auto pos = m_pPlayer->getPosition() + Vec2(0,size.height/2);
	m_pDelegate->shootTo(pos);
}
void GameLayer::gameOver(Ref*)
{
	auto life = DynamicData::getInstance()->getPlayerLives() - 1;
	if(life <= 0)
	{
		life = 0;
		m_pDelegate->gameOver();
	}
	DynamicData::getInstance()->setPlayerLives(life);
}