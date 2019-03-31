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
	//������Դ
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("fish.plist");
	//���ؽű�
	LuaEngine::getInstance()->dofile("main.lua");
	//���ص�һ�ؽű�
	LuaEngine::getInstance()->dofile("level/level1.lua");
	//�¼��ַ���
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//��Ϸ��
	m_pGameLayer = GameLayer::create();
	this->addChild(m_pGameLayer);
	//fish layer
	m_pFishLayer = FishLayer::create();
	this->addChild(m_pFishLayer);
	//
	this->scheduleUpdate();
	//�����ײ������
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
	//a ������� b���
	if((filterA.categoryBits == 0x02 && filterB.categoryBits == 0x04))
	{
		Fish*fish = static_cast<Fish*>(entity1);
		fish->runScaredAnimation();
	}
	//a ��� b�������
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x02)
	{
			Fish*fish = static_cast<Fish*>(entity2);
			fish->runScaredAnimation();
	}
	//a �� b ���
	else if(filterA.categoryBits == 0x01 && filterB.categoryBits == 0x04)
	{
		Fork*fork = static_cast<Fork*>(entity2);
		//ֻ����������ڲ���ʱ�Ż������ײ�ж�
		if(fork->isShooting() == true)
		{
			Fish*fish = static_cast<Fish*>(entity1);
			fish->catched();
		}
	}
	//a��� b��
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x01)
	{
		Fork*fork = static_cast<Fork*>(entity1);
		//ֻ����������ڲ���ʱ�Ż������ײ�ж�
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