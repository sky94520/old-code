#include "GameScene.h"
#include "OperatorLayer.h"
#include "StateLayer.h"
#include "Hero.h"
#include "Enemy.h"
#include "Global.h"
USING_NS_CC;
GameScene::GameScene()
{
	Global::getInstance()->m_pGameLayer = this;
}
Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    // ��Ϸ��
    auto gameLayer = GameScene::create();
    scene->addChild(gameLayer,0);
	//������
	auto operatorLayer = OperatorLayer::create();
	scene->addChild(operatorLayer,1);
	//չʾ��
	auto stateLayer = StateLayer::create();
	scene->addChild(stateLayer,2);
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//�޸ı���ͼƬ
	Sprite*bg = Sprite::create("background_1.jpg");
	this->addChild(bg,0);
	bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	//������˹�
	m_pHero = Hero::create();
	m_pHero->setPosition(Point(400,200));
	this->addChild(m_pHero,5);
	//���Ӹ�����
	Enemy*enemy = Enemy::create();
	enemy->setPosition(Point(CCRANDOM_0_1()*visibleSize.width,CCRANDOM_0_1()*300));
	Enemy*enemy2 = Enemy::create();
	enemy2->setPosition(Point(CCRANDOM_0_1()*visibleSize.width,CCRANDOM_0_1()*300));
	this->addChild(enemy);
	this->addChild(enemy2);
	
	this->scheduleUpdate();
    return true;
}
void GameScene::update(float dt)
{
	m_pHero->updateSelf();
}

