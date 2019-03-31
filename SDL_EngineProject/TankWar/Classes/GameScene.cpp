#include "GameScene.h"
#include "EventLayer.h"
#include "TankLayer.h"
#include "StaticData.h"
#include "Tank.h"

GameScene* GameScene::s_pInstance = nullptr;

GameScene::GameScene()
	:m_pEventLayer(nullptr)
	,m_pTankLayer(nullptr)
{
}

GameScene::~GameScene()
{
	StaticData::purge();
}

GameScene* GameScene::getInstance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new GameScene();
		s_pInstance->init();
	}
	return s_pInstance;
}

void GameScene::purge()
{
	SDL_SAFE_RELEASE_NULL(s_pInstance);
}

bool GameScene::init()
{
	this->preloadResources();
	//TODO
	Director::getInstance()->getRenderer()->setRenderDrawColor(Color4B(0, 255, 255, 255));
	//创建各种层
	auto platform = Director::getInstance()->getPlatform();

	if (platform == "Windows")
		m_pEventLayer = KeyboardEventLayer::create();
	else if (platform == "Android")
		;
	this->addChild(m_pEventLayer);
	//坦克层
	m_pTankLayer = TankLayer::create();
	this->addChild(m_pTankLayer);

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float dt)
{
	m_pEventLayer->update(dt);
}

void GameScene::moveBegin(Direction direction)
{
	m_pTankLayer->getPlayer()->move(direction);
}

void GameScene::moveEnd()
{
	m_pTankLayer->getPlayer()->sit();
}

void GameScene::fire()
{
	m_pTankLayer->getPlayer()->fire();
}

void GameScene::preloadResources()
{
	auto frameCache = Director::getInstance()->getSpriteFrameCache();

	frameCache->addSpriteFramesWithFile("sprite/res.xml");
	//加载静态文件
	StaticData::getInstance();
	//加载动画文件
	AnimationCache::getInstance()->addAnimationsWithFile("data/animation.plist");
}