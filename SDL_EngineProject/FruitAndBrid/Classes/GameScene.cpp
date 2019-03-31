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
	//¼ÓÔØÍ¼Æ¬
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("pic/bird.xml","pic/bird.png");
	//¼ÇÔØÒôÀÖ£¬ÒôĞ§
	SoundManager::getInstance()->preloadEffect("sounds/sfx_die.ogg");
	//±³¾°²ã
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer,-1);
	//ÕÏ°­²ã
	m_pColumnLayer = ColumnLayer::create();
	m_pColumnLayer->setSpeed(3.f);
	this->addChild(m_pColumnLayer);
	//Ğ¡Äñ²ã
	m_pBirdLayer = BirdLayer::create();
	this->addChild(m_pBirdLayer);
	//ÊÂ¼ş
	auto keyBoard = EventListenerKeyboard::create();
	keyBoard->onKeyReleased = SDL_CALLBACK_2(GameScene::handleEvent,this);

	_eventDispatcher->addEventListener(keyBoard,this);
	//Ìí¼Ó´¥Åö¼àÌı
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
	//ÄñÅö×²ÇøÓò
	auto bird = m_pBirdLayer->getBird();
	Rect r1 = bird->getBoundingBox();
	//Öù×Ó
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