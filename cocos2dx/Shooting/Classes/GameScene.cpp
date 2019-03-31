#include "GameScene.h"
#include "BackgroundLayer.h"
#include "Arrow.h"
GameScene::GameScene()
	:m_pBackgroundLayer(nullptr),m_pTiledMapLayer(nullptr)
	,m_pGameLayer(nullptr),m_pTouchLayer(nullptr)
{
}
GameScene::~GameScene()
{
}
bool GameScene::init()
{
	//加载资源
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("texture.plist","texture.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建背景
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer,-1);
	//创建地图
	m_pTiledMapLayer = TiledMapLayer::create("map1.tmx");
	this->addChild(m_pTiledMapLayer);
	//创建游戏主界面
	m_pGameLayer = GameLayer::create(this);
	this->addChild(m_pGameLayer);
	//发放触摸
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//获取偏移位置
	//auto offsetX = -(m_pTiledMap->getContentSize().width - visibleSize.width)/2;
	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	//检测碰撞
	checkCollistion();
}
void GameScene::checkCollistion()
{
	auto pArrow = m_pGameLayer->getArrow();
	//如果箭已经发射才检测
	if(pArrow->isAlive())
	{
		//获取绝对坐标
		auto pos = pArrow->getPosition();
		//获取该坐标下的GID
		auto valueMap = m_pTiledMapLayer->getValueMapByPosition("logicLayer",pos);
		if(valueMap.empty())
			return;
		else
			pArrow->end();
	}
}
ValueMap GameScene::getObject(const std::string&name)
{
	return m_pTiledMapLayer->getObject(name);
}
void GameScene::arrowAimAt(const Point&pos)
{
	m_pGameLayer->aimAt(pos);
}
void GameScene::arrowShootTo(const Point&pos)
{
	m_pGameLayer->shootTo(pos);
}