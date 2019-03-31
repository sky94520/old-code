#include "GameScene.h"
#include "BrickLayer.h"
#include "Brick.h"
#include "PanelLayer.h"
#include "DynamicData.h"

GameScene::GameScene()
	:m_pEventLayer(nullptr),
	m_pMapLayer(nullptr),m_pBrickLayer(nullptr)
	,m_pPanelLayer(nullptr),m_pGameOverLayer(nullptr)
{
	srand(time(NULL));
}
GameScene::~GameScene()
{
	DynamicData::getInstance()->purge();
}
bool GameScene::init()
{
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("resources.xml");
	//Ìí¼ÓÒôÀÖ
	SoundManager::getInstance()->preloadBackgroundMusic("gameBG.ogg");
	SoundManager::getInstance()->preloadEffect("gameover.wav");
	SoundManager::getInstance()->preloadEffect("down.ogg");
	SoundManager::getInstance()->preloadEffect("move.ogg");
	SoundManager::getInstance()->preloadEffect("rotate.ogg");
	SoundManager::getInstance()->preloadEffect("delete.ogg");

	//ÊÂ¼þ·Ö·¢²ã
	m_pEventLayer = EventLayer::create();
	m_pEventLayer->setDelegate(this);
	this->addChild(m_pEventLayer);
	//µØÍ¼²ã
	m_pMapLayer = MapLayer::create();
	this->addChild(m_pMapLayer,-1);
	//·½¿é²ã
	m_pBrickLayer = BrickLayer::create(this);
	this->addChild(m_pBrickLayer); 
	//ÏÔÊ¾²ã
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//ÓÎÏ·½áÊø²ã
	m_pGameOverLayer = GameOverLayer::create();
	m_pGameOverLayer->hide();

	m_pGameOverLayer->setDelegate(this);
	this->addChild(m_pGameOverLayer);

	this->scheduleUpdate();
	//²¥·Å±³¾°ÒôÀÖ
	SoundManager::getInstance()->playBackgroundMusic("gameBG.ogg",-1);
	return true;
}
void GameScene::update(float dt)
{
	m_pMapLayer->update(dt);
	m_pBrickLayer->update(dt);
	m_pEventLayer->update(dt);
}
void GameScene::gameOver()
{
	SoundManager::getInstance()->playEffect("gameover.wav",0);
	this->gamePause();
	
	m_pGameOverLayer->show();
}
void GameScene::gameRetry()
{
	this->gameResume();
	m_pGameOverLayer->hide();
	DynamicData::getInstance()->reset();

	//ÖØÖÃMapLayer BrickLayer DynamicData
	m_pMapLayer->reset();
	m_pBrickLayer->reset();
}
void GameScene::gamePause()
{
	m_pEventLayer->onExit();
	m_pBrickLayer->onExit();

	this->unscheduleUpdate();
}
void GameScene::gameResume()
{
	m_pEventLayer->onEnter();
	m_pBrickLayer->onEnter();

	this->scheduleUpdate();
}
Rect GameScene::getClientRect()const
{
	return m_pMapLayer->getClientRect();
}
bool GameScene::isCollided(Brick*brick)
{
	return m_pMapLayer->isCollided(brick);
}
void GameScene::insertBrick(Brick*brick)
{
	m_pMapLayer->insertBrick(brick);
}
int GameScene::clearUpLineNum()
{
	return m_pMapLayer->clearUpBrick();
}
void GameScene::onKeyPressed(SDL_Keycode keyCode,SDL_Event*event)
{
	m_pBrickLayer->onKeyPressed(keyCode,event);
}
CollideResult GameScene::isGameOver(Brick*pBrick)
{
	return m_pMapLayer->isGameOver(pBrick);
}