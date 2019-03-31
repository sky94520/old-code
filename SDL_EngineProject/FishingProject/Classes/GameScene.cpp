#include "GameScene.h"
#include "GameLayer.h"
#include "FishLayer.h"
#include "Fork.h"
#include "Fish.h"
#include "LuaEngine.h"
#include "PhysicalEngine.h"

GameScene::GameScene()
	:m_pGameLayer(nullptr),m_pFishLayer(nullptr)
	,m_pTouchLayer(nullptr)
{
}
GameScene::~GameScene()
{
	LuaEngine::getInstance()->purge();
}
bool GameScene::init()
{
	//加载资源
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("fish.plist");
	//加载脚本
	LuaEngine::getInstance()->dofile("main.lua");
	//加载第一关脚本
	LuaEngine::getInstance()->dofile("level/level1.lua");
	//事件分发层
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//游戏层
	m_pGameLayer = GameLayer::create();
	this->addChild(m_pGameLayer);
	//fish layer
	m_pFishLayer = FishLayer::create();
	this->addChild(m_pFishLayer);
	//
	this->scheduleUpdate();
	//添加碰撞监听器
	PhysicalEngine::getInstance()->SetContactListener(this);

	return true;
}
void GameScene::update(float dt)
{
	PhysicalEngine::getInstance()->update(dt);

	m_pFishLayer->update(dt);
}
void GameScene::shoot(const Point&targetPos)
{
	auto fork = m_pGameLayer->getFork();
	if(fork->isShooting())
		return;
	fork->setVisible(true);
	fork->shoot(targetPos);
}
void GameScene::BeginContact(b2Contact* contact)
{
	b2Fixture*fixtureA = contact->GetFixtureA();
	b2Fixture*fixtureB = contact->GetFixtureB();
	b2Filter filterA = fixtureA->GetFilterData();
	b2Filter filterB = fixtureB->GetFilterData();
	Entity*entity1 = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity*entity2 = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if(entity1->isVisible() == false || entity2->isVisible() == false)
		return;
	//a 惊吓面积 b鱼叉
	if((filterA.categoryBits == 0x02 && filterB.categoryBits == 0x04))
	{
		Fish*fish = static_cast<Fish*>(entity1);
		fish->runScaredAnimation();
	}
	//a 鱼叉 b惊吓面积
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x02)
	{
			Fish*fish = static_cast<Fish*>(entity2);
			fish->runScaredAnimation();
	}
	//a 鱼 b 鱼叉
	else if(filterA.categoryBits == 0x01 && filterB.categoryBits == 0x04)
	{
		Fork*fork = static_cast<Fork*>(entity2);
		//只有在鱼叉正在捕鱼时才会进行碰撞判定
		if(fork->isShooting() == true)
		{
			Fish*fish = static_cast<Fish*>(entity1);
			fish->catched();
		}
	}
	//a鱼叉 b鱼
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x01)
	{
		Fork*fork = static_cast<Fork*>(entity1);
		//只有在鱼叉正在捕鱼时才会进行碰撞判定
		if(fork->isShooting() == true)
		{
			Fish*fish = static_cast<Fish*>(entity2);
			fish->catched();
		}
	}
}
void GameScene::EndContact(b2Contact* contact)
{
}
void GameScene::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(GameScene::onDraw,this,transform,flags);
	renderer->addCommand(&_command);
}
void GameScene::onDraw(const Mat4 &transform, uint32_t flags)
{
	PhysicalEngine::getInstance()->draw(transform,flags);
}