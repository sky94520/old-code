#include "GameScene.h"
#include "BackgroundLayer.h"
#include "BirdLayer.h"
#include "ColumnLayer.h"
#include "Bird.h"
#include "DoubleColumn.h"

GameScene::GameScene()
	:m_pBackgroundLayer(nullptr)
	,m_pBirdLayer(nullptr)
	,m_pColumnLayer(nullptr)
{
}
GameScene::~GameScene()
{
}
bool GameScene::init()
{
	//����ͼƬ
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("pic/bird.xml","pic/bird.png");
	//�������֣���Ч
	SoundManager::getInstance()->preloadEffect("sounds/sfx_die.ogg");
	//������
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer,-1);
	//�ϰ���
	m_pColumnLayer = ColumnLayer::create();
	m_pColumnLayer->setSpeed(3.f);
	this->addChild(m_pColumnLayer);
	//С���
	m_pBirdLayer = BirdLayer::create();
	this->addChild(m_pBirdLayer);
	//�¼�
	auto keyBoard = EventListenerKeyboard::create();
	keyBoard->onKeyReleased = SDL_CALLBACK_2(GameScene::handleEvent,this);

	_eventDispatcher->addEventListener(keyBoard,this);
	//��Ӵ�������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = SDL_CALLBACK_2(GameScene::onTouchBegan,this);
	_eventDispatcher->addEventListener(listener,this);

	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	m_pBackgroundLayer->update(dt);
	m_pBirdLayer->update(dt);
	m_pColumnLayer->update(dt);
	//handle collision
	this->handleCollision();
}
void GameScene::handleEvent(SDL_Keycode keyCode,SDL_Event*event)
{
	if(keyCode == SDLK_SPACE)
		m_pBirdLayer->birdFly(keyCode,event);
}
bool GameScene::onTouchBegan(Touch*touch,SDL_Event*event)
{
	m_pBirdLayer->birdFly(SDLK_SPACE,event);
	return false;
}
void GameScene::handleCollision()
{
	//����ײ����
	auto bird = m_pBirdLayer->getBird();
	Rect r1 = bird->getBoundingBox();
	//����
	auto columns = m_pColumnLayer->getColumns();
	for(auto column:columns)
	{
		if(column->isAvaiable() && column->checkCollision(r1))
		{
			//bird->dead();
			printf("the bird is dead\n");
		}
	}
}